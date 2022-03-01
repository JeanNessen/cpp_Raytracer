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
    static int recursion_depth;

    std::vector<PointLight> world_lights{};

    std::vector<Shape_ptr> world_objects{};

    Color GetColorForPixel(Camera c, int x, int y);

    void PrintProgressUpdate(int lines_total, int lines_remaining, Camera c);

public:

    int GetRecursionDepth(){ return recursion_depth; }
    void SetRecursionDepth(int new_depth){ recursion_depth = new_depth; }

    std::vector<PointLight>& GetWorldLights(){ return world_lights; }
    void AddLight(PointLight light);

    std::vector<Shape_ptr> GetWorldObjects(){ return world_objects; }
    void AddObject(Shape_ptr obj);

    std::vector<Intersection> IntersectWorld(Ray ray);

    bool IsShadowed(Point p);
    Color ReflectedColor(IntersectionComputations comps, int remaining = recursion_depth);

    Color ShadeHit(IntersectionComputations comps, int remaining = recursion_depth);

    Color ColorAt(Ray r, int remaining = recursion_depth);

    Canvas RenderSingleThread(Camera c);
};

World DefaultWorld();

#endif //CPP_RAYTRACER_WORLD_H
