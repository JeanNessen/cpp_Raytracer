//
// Created by Jean-Luc von Nessen on 24.01.22.
//
#pragma once

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"
#include "Canvas.h"
#include "Camera.h"
#include "IntersectionComputations.h"


class World {
//Methods
private:

    Color GetColorForPixel(Camera c, int x, int y);

    Canvas ExecuteRenderPass(Camera c);

    void PrintProgressUpdate(int lines_total, int lines_remaining, Camera c);

public:

    static int GetRecursionDepth(){ return m_recursion_depth; }
    void SetRecursionDepth(int new_depth){ m_recursion_depth = new_depth; }

    std::vector<PointLight>& GetWorldLights(){ return m_world_lights; }
    void AddLight(PointLight light);

    std::vector<Shape_ptr>& GetWorldObjects(){ return m_world_objects; }
    void AddObject(Shape_ptr obj);

    std::vector<Intersection> IntersectWorld(Ray ray);

    bool CalculateShadow(Point p);

    Color CalculateReflectedColor(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color CalculateRefractedColor(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color ShadeHit(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color CalculateColorAt(Ray r, int remaining = m_recursion_depth);

    Canvas RenderSingleThread(Camera c);

//Members
private:

    static int m_recursion_depth;

    std::vector<PointLight> m_world_lights{};

    std::vector<Shape_ptr> m_world_objects{};

public:
};

World DefaultWorld();

