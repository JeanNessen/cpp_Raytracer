//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include "world.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <thread>
#include <future>



//static variables
int world::m_recursion_depth = 5;
std::atomic<int> world::m_remaining_lines;

using namespace std::chrono_literals;

world DefaultWorld() {
    world w{};

    point_light default_light{color(1, 1, 1), point(-10, 10, -10)};
    w.add_light(default_light);

    sphere_ptr default_sphere_1 (new Sphere());
    default_sphere_1->get_material().color = color(0.8, 1.0, 0.6);
    default_sphere_1->get_material().diffuse = 0.7;
    default_sphere_1->get_material().specular = 0.2;

    w.add_object(default_sphere_1);

    sphere_ptr default_sphere_2 (new Sphere());
    default_sphere_2->set_transform(Math::Scaling(0.5, 0.5, 0.5));

    w.add_object(default_sphere_2);

    return w;
}

void world::add_light(point_light light) {
    m_world_lights.push_back(light);
}

void world::add_object(shape_ptr obj) {
    m_world_objects.push_back(obj);
}

std::vector<intersection> world::intersect_world(ray ray) {

    std::vector<std::unique_ptr<intersection>> world_intersections_ptr;

    //Add all the intersections to the vector
    for (const auto& obj: m_world_objects) {
        std::vector<intersection> intersections = ray.intersect(obj);

        for (auto i: intersections) {
            world_intersections_ptr.push_back(std::make_unique<intersection>(i));
        }
    }

    //Sort the pointer vector
    std::sort(world_intersections_ptr.begin(), world_intersections_ptr.end(), [](std::unique_ptr<intersection>& lhs, std::unique_ptr<intersection>& rhs) {
        return lhs->t > rhs->t;
    });

    //Make new vector with sorted Intersections
    std::vector<intersection> world_intersections;

    world_intersections.reserve(world_intersections_ptr.size());

    //Reverse the vector
    for (int i = 0; i < world_intersections_ptr.size(); ++i) {
        world_intersections.push_back(*(world_intersections_ptr[world_intersections_ptr.size()-i-1]));
    }

    return world_intersections;
}

color world::shade_hit(intersection_computations comps, int remaining) {
    color surface = Lighting(comps.object->get_material_const(),
                              comps.object,
                              m_world_lights[0],
                              comps.over_point,
                              comps.eye_v,
                              comps.normal_v,
                              calculate_shadow(comps.over_point));

    color reflected = calculate_reflected_color(comps, remaining);
    color refracted = calculate_refracted_color(comps, remaining);

    material material = comps.object->get_material();
    if (material.reflective > 0 && material.transparency > 0)
    {
        double reflectance = Schlick(comps);
        return surface + reflected * reflectance + refracted * (1-reflectance);
    }
    else
    {
        return surface + reflected + refracted;

    }
}

//TODO Bounce light for diffuse materials
color world::calculate_color_at(ray r, int remaining) {

    std::vector<intersection> intersections = intersect_world(r);

    if(!intersections.empty() && hit(intersections))
    {
        intersection currentHit = *hit(intersections);
        intersection_computations comps = PrepareComputations(currentHit, r);
        color color = shade_hit(comps, remaining);
        return color;
    }
    else
    {
        return colors::black;
    }

}

canvas world::render_multi_thread(camera c, int num_threads) {

    auto start = std::chrono::high_resolution_clock::now();

    if(c.get_samples_per_pixel() < num_threads)
    {
        num_threads = c.get_samples_per_pixel();
    }

    std::cout << "Starting render using " << num_threads << " threads." << std::endl;

    canvas image_sum{c.get_h_size(), c.get_v_size()};

    //Set m_remaining_lines to the total number of lines to be calculated.
    m_remaining_lines = c.get_samples_per_pixel() * c.get_v_size();
    m_total_lines = m_remaining_lines;

    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    std::vector<std::future<canvas>> render_pass_canvases;
    render_pass_canvases.reserve(num_threads);

    //calculate number of passes per thread

    int num_passes_last_thread = c.get_samples_per_pixel() % num_threads;
    int num_passes_per_thread{ 0 };
    if(num_passes_last_thread > 0)
    {
        num_passes_per_thread = c.get_samples_per_pixel() / (num_threads - 1);
    }
    else
    {
        num_passes_per_thread = c.get_samples_per_pixel() / num_threads;
        num_passes_last_thread = num_passes_per_thread;
    }

    
    for (int i = 0; i < num_threads; ++i) {
        std::cout << "Starting render pass " << i + 1 << " of " << c.get_samples_per_pixel() << "." << std::endl;
        if(i == num_threads-1)
        {
            render_pass_canvases.push_back(std::async(&world::execute_multiple_passes, this, c, num_passes_last_thread));
        }
        else
        {
            render_pass_canvases.push_back(std::async(&world::execute_multiple_passes, this, c, num_passes_per_thread));
        }
    }

    while(m_remaining_lines > 0)
    {
        print_progress_update();
        std::this_thread::sleep_for(1s);
    }


    for (auto& render_pass_canvas : render_pass_canvases)
    {
	    render_pass_canvas.wait();
    }
    
    for (auto& render_pass_canvas : render_pass_canvases)
    {
        image_sum += render_pass_canvas.get();
    }
    
    canvas image_average = image_sum / num_threads;



    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    double seconds = duration.count() / 1000.0f;

    std::cout << "Finished in " << seconds << " seconds with " << c.get_samples_per_pixel()  << " samples per pixel on one" << " thread." << std::endl;

    return image_average;
}


canvas world::execute_single_pass(camera c) {
    canvas image{c.get_h_size(), c.get_v_size()};

	for (int y = 0; y < c.get_v_size(); ++y) 
    {
		for (int x = 0; x < c.get_h_size(); ++x) 
        {
			color color = get_color_for_pixel(c, x, y);
			image.write_pixel(x, y, color);
		}
		--m_remaining_lines;
	}
    return image;
}

canvas world::execute_multiple_passes(camera c, int num_passes)
{
    canvas image{ c.get_h_size(), c.get_v_size() };

    for (int i = 0; i < num_passes; ++i)
    {
        image += execute_single_pass(c);
    }

    return image / num_passes;
}

bool world::calculate_shadow(point p) {
    vector v_point_to_light{m_world_lights[0].position - p};
    double distance_to_light = (v_point_to_light).magnitude();
    vector direction_to_light = v_point_to_light.normalized();

    ray r_point_to_light{p, direction_to_light};

    std::vector<intersection> intersections = intersect_world(r_point_to_light);

    if(intersection* currentHit = hit(intersections))
    {
        bool blocking_shape_throws_shadow = currentHit->object->get_material().throws_shadow;
        if (currentHit->t < distance_to_light && blocking_shape_throws_shadow)
        {
            return true;
        }
    }

    return false;
}

color world::calculate_reflected_color(intersection_computations comps, int remaining) {
    if(comps.object->get_material().reflective == 0 || remaining <= 0)
    {
        return colors::black;
    } else
    {
        ray reflected_ray{comps.over_point, comps.reflect_v};
        color color = calculate_color_at(reflected_ray, remaining - 1);

        return color * comps.object->get_material().reflective;
    }
}

color world::get_color_for_pixel(camera c, int x, int y) {
    ray r = c.ray_for_pixel(x, y);
    color pixel_color = calculate_color_at(r);
    return pixel_color;
}

void world::print_progress_update() const
{
	const double remaining_percentage = static_cast<double>(m_remaining_lines) / static_cast<double>(m_total_lines);
	const double progress_percentage = 100 - remaining_percentage * 100;

	std::cout.precision(4);
	std::cout << "Progress: " << progress_percentage << "%" << std::endl;
}

color world::calculate_refracted_color(intersection_computations comps, int remaining)
{
    //Aplly snells law to check for total internal reflection
    double n_ratio = comps.n1 / comps.n2;
    double cos_i = Math::Dot(comps.eye_v, comps.normal_v);
    double sin2_t = std::pow(n_ratio, 2) * (1 - std::pow(cos_i, 2));



    if (comps.object->get_material().transparency == 0)
    {
        return colors::black;
    }
    else if(remaining == 0)
    {
        return colors::black;
    }
    else if(sin2_t > 1)
    {
        return colors::black;
    }
    else
    {
        double cos_t = sqrt(1 - sin2_t);

        vector direction {comps.normal_v * (n_ratio * cos_i - cos_t) -
                comps.eye_v * n_ratio};

        ray refracted_ray{comps.under_point, direction};

        return calculate_color_at(refracted_ray, remaining - 1) * comps.object->get_material().transparency;
    }
}




