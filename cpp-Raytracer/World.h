//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#ifndef CPP_RAYTRACER_WORLD_H
#define CPP_RAYTRACER_WORLD_H

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"


class World {
private:

    std::vector<PointLight> world_lights{};

    std::vector<Sphere> world_objects{};

public:

    std::vector<PointLight> GetWorldLights(){ return world_lights; }

    void AddLight(PointLight light);

    std::vector<Sphere> GetWorldObjects(){ return world_objects; }

    void AddObject(Sphere obj);

    std::vector<Intersection> IntersectWorld(Ray ray);


};

World DefaultWorld();

#endif //CPP_RAYTRACER_WORLD_H
