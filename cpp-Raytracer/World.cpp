//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include "World.h"

#include <memory>
#include <iostream>
#include <chrono>

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
        for (Intersection i: intersections) {
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

    return surface + reflected;
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
        return Color(0, 0, 0);
    }

}

Canvas World::Render(Camera c) {
    auto start = std::chrono::high_resolution_clock::now();
    int ray_count = 0;

    Canvas image{c.GetHSize(), c.GetVSize()};

    for (int y = 0; y < c.GetVSize()-1; ++y) {
        for (int x = 0; x < c.GetHSize(); ++x) {
            Ray ray = c.RayForPixel(x, y);
            Color color = ColorAt(ray);
            image.write_pixel(x, y, color);
            ++ray_count;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    double seconds = duration.count() / 1000.0f;

    std::cout << ray_count << " rays rendered in " << seconds << " seconds." << std::endl;

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
