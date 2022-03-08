//
// Created by Jean-Luc von Nessen on 24.01.22.
//
#pragma once

#include <vector>
#include "CSphere.h"
#include "Light.h"
#include "CRay.h"
#include "CCanvas.h"
#include "CCamera.h"
#include "SIntersectionComputations.h"


class CWorld {
private:
    static int recursion_depth;

    std::vector<SPointLight> world_lights{};

    std::vector<Shape_ptr> world_objects{};

    CColor GetColorForPixel(CCamera c, int x, int y);

    CCanvas ExecuteRenderPass(CCamera c);

    void PrintProgressUpdate(int lines_total, int lines_remaining, CCamera c);

public:

    static int GetRecursionDepth(){ return recursion_depth; }
    void SetRecursionDepth(int new_depth){ recursion_depth = new_depth; }

    std::vector<SPointLight>& GetWorldLights(){ return world_lights; }
    void AddLight(SPointLight light);

    std::vector<Shape_ptr>& GetWorldObjects(){ return world_objects; }
    void AddObject(Shape_ptr obj);

    std::vector<SIntersection> IntersectWorld(CRay ray);

    bool CalculateShadow(Point p);

    CColor CalculateReflectedColor(SIntersectionComputations comps, int remaining = recursion_depth);

    CColor CalculateRefractedColor(SIntersectionComputations comps, int remaining = recursion_depth);

    CColor ShadeHit(SIntersectionComputations comps, int remaining = recursion_depth);

    CColor CalculateColorAt(CRay r, int remaining = recursion_depth);

    CCanvas RenderSingleThread(CCamera c);
};

CWorld DefaultWorld();

