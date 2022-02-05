//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include "World.h"

#include <memory>
#include <iostream>

World DefaultWorld() {
    World w{};

    PointLight default_light{Color(1, 1, 1), Point(-10, 10, -10)};
    w.AddLight(default_light);

    Sphere default_sphere_1{1};
    default_sphere_1.GetMaterial().color = Color(0.8, 1.0, 0.6);
    default_sphere_1.GetMaterial().diffuse = 0.7;
    default_sphere_1.GetMaterial().specular = 0.2;

    w.AddObject(default_sphere_1);

    Sphere default_sphere_2{2};
    default_sphere_2.SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    w.AddObject(default_sphere_2);

    return w;
}

void World::AddLight(PointLight light) {
    world_lights.push_back(light);
}

void World::AddObject(Sphere obj) {
    world_objects.push_back(obj);
}

std::vector<Intersection> World::IntersectWorld(Ray ray) {

    std::vector<std::unique_ptr<Intersection>> world_intersections_ptr;

    //Add all the intersections to the vector
    for (Sphere obj: world_objects) {
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
