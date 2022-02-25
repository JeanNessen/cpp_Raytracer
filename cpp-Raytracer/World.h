//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#ifndef CPP_RAYTRACER_WORLD_H
#define CPP_RAYTRACER_WORLD_H

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"
#include "Canvas.h"
#include "Camera.h"
#include "IntersectionComputations.h"


class World {
private:

    std::vector<PointLight> world_lights{};

    std::vector<Shape_ptr> world_objects{};

public:

    std::vector<PointLight>& GetWorldLights(){ return world_lights; }
    void AddLight(PointLight light);

    std::vector<Shape_ptr> GetWorldObjects(){ return world_objects; }
    void AddObject(Shape_ptr obj);

    std::vector<Intersection> IntersectWorld(Ray ray);

    bool IsShadowed(Point p);
    Color ReflectedColor(IntersectionComputations comps, int remaining = 5);

    Color ShadeHit(IntersectionComputations comps, int remaining = 5);

    Color ColorAt(Ray r, int remaining = 5);

    Canvas Render(Camera c);
};

World DefaultWorld();

#endif //CPP_RAYTRACER_WORLD_H
