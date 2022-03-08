//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include "World.h"

#include <iostream>
#include <chrono>


//static variables
int World::recursion_depth = 5;

World DefaultWorld() {
    World w{};

    PointLight default_light{Color(1, 1, 1), Point(-10, 10, -10)};
    w.AddLight(default_light);

    Sphere_ptr default_sphere_1 (new Sphere());
    default_sphere_1->GetMaterial().color = Color(0.8, 1.0, 0.6);
    default_sphere_1->GetMaterial().diffuse = 0.7;
    default_sphere_1->GetMaterial().specular = 0.2;

    w.AddObject(default_sphere_1);

    Sphere_ptr default_sphere_2 (new Sphere());
    default_sphere_2->SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    w.AddObject(default_sphere_2);

    return w;
}

void World::AddLight(PointLight light) {
    world_lights.push_back(light);
}

void World::AddObject(Shape_ptr obj) {
    world_objects.push_back(obj);
}

std::vector<Intersection> World::IntersectWorld(Ray ray) {

    std::vector<std::unique_ptr<Intersection>> world_intersections_ptr;

    //Add all the intersections to the vector
    for (const auto& obj: world_objects) {
        std::vector<Intersection> intersections = ray.Intersect(obj);

        for (auto i: intersections) {
            world_intersections_ptr.push_back(std::make_unique<Intersection>(i));
        }
    }

    //Sort the pointer vector
    std::sort(world_intersections_ptr.begin(), world_intersections_ptr.end(), [](std::unique_ptr<Intersection>& lhs, std::unique_ptr<Intersection>& rhs) {
        return lhs->t > rhs->t;
    });

    //Make new vector with sorted Intersections
    std::vector<Intersection> world_intersections;

    world_intersections.reserve(world_intersections_ptr.size());

    //Reverse the Vector
    for (int i = 0; i < world_intersections_ptr.size(); ++i) {
        world_intersections.push_back(*(world_intersections_ptr[world_intersections_ptr.size()-i-1]));
    }

    return world_intersections;
}

Color World::ShadeHit(IntersectionComputations comps, int remaining) {
    Color surface = Lighting(comps.object->GetMaterialConst(),
                    comps.object,
                    world_lights[0],
                    comps.over_point,
                    comps.eye_v,
                    comps.normal_v,
                    IsShadowed(comps.over_point));

    Color reflected = ReflectedColor(comps, remaining);
    Color refracted = RefractedColor(comps, remaining);

    Material material = comps.object->GetMaterial();
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

Color World::ColorAt(Ray r, int remaining) {

    std::vector<Intersection> intersections = IntersectWorld(r);

    if(!intersections.empty() && Hit(intersections))
    {
        Intersection hit = *Hit(intersections);
        IntersectionComputations comps = PrepareComputations(hit, r);
        Color color = ShadeHit(comps, remaining);
        return color;
    }
    else
    {
        return color::black;
    }

}

Canvas World::RenderSingleThread(Camera c) {

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Starting render using one thread." << std::endl;

    Canvas image_sum{c.GetHSize(), c.GetVSize()};

    //Do one render pass per sample
    for (int i = 0; i < c.GetSamplesPerPixel(); ++i) {
        std::cout << "Starting render pass " << i+1 << " of " << c.GetSamplesPerPixel() << "." << std::endl;
        image_sum += RenderPass(c);
        std::cout << "Finished render pass " << i+1 << "." << std::endl;
    }

    Canvas image_average = image_sum / c.GetSamplesPerPixel();



    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    double seconds = duration.count() / 1000.0f;

    std::cout << "Finished in " << seconds << " seconds with " << c.GetSamplesPerPixel()  << " samples per pixel on one" << " thread." << std::endl;

    return image_average;
}


Canvas World::RenderPass(Camera c) {
    Canvas image{c.GetHSize(), c.GetVSize()};

    int lines_remaining = c.GetVSize();

    for (int y = 0; y < c.GetVSize()-1; ++y) {
    #pragma omp parallel
        #pragma omp for
        for (int x = 0; x < c.GetHSize(); ++x) {
            Color color = GetColorForPixel(c, x, y);
            image.WritePixel(x, y, color);
        }
        PrintProgressUpdate(c.GetVSize(), --lines_remaining, c);
    }
    return image;
}

bool World::IsShadowed(Point p) {
    Vector v_point_to_light{world_lights[0].position - p};
    double distance_to_light = (v_point_to_light).magnitude();
    Vector direction_to_light = v_point_to_light.normalized();

    Ray r_point_to_light{p, direction_to_light};

    std::vector<Intersection> intersections = IntersectWorld(r_point_to_light);

    if(Hit(intersections) && Hit(intersections)->t < distance_to_light)
    {
        return true;
    } else
    {
        return false;
    }
}

Color World::ReflectedColor(IntersectionComputations comps, int remaining) {
    if(comps.object->GetMaterial().reflective == 0 || remaining <= 0)
    {
        return color::black;
    } else
    {
        Ray reflected_ray{comps.over_point, comps.reflect_v};
        Color color = ColorAt(reflected_ray, remaining-1);

        return color * comps.object->GetMaterial().reflective;
    }
}

Color World::GetColorForPixel(Camera c, int x, int y) {
    Ray r = c.RayForPixel(x, y);
    Color pixel_color = ColorAt(r);
    return pixel_color;
}

void World::PrintProgressUpdate(int lines_total, int lines_remaining, Camera c) {
    if (lines_remaining % 10 == 0)
    {
        double remaining_percentage = double(lines_remaining) / double(lines_total);
        double progress_percentage = 100 - remaining_percentage * 100;

        std::cout.precision(4);
        std::cout << "Progress: " << progress_percentage << "%" << std::endl;
    }
}

Color World::RefractedColor(IntersectionComputations comps, int remaining)
{
    //Aplly snells law to check for total internal reflection
    double n_ratio = comps.n1 / comps.n2;
    double cos_i = Math::Dot(comps.eye_v, comps.normal_v);
    double sin2_t = std::pow(n_ratio, 2) * (1 - std::pow(cos_i, 2));



    if (comps.object->GetMaterial().transparency == 0)
    {
        return color::black;
    }
    else if(remaining == 0)
    {
        return color::black;
    }
    else if(sin2_t > 1)
    {
        return color::black;
    }
    else
    {
        double cos_t = sqrt(1 - sin2_t);

        Vector direction {comps.normal_v * (n_ratio * cos_i - cos_t) -
                comps.eye_v * n_ratio};

        Ray refracted_ray{comps.under_point, direction};

        return ColorAt(refracted_ray, remaining-1) * comps.object->GetMaterial().transparency;
    }
}




