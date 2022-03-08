//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#ifndef CPP_RAYTRACER_LIGHT_H
#define CPP_RAYTRACER_LIGHT_H

#include "CColor.h"
#include "CMaterial.h"
#include "Math.h"
#include "CShape.h"

struct SPointLight{
    CColor intensity{};
    Point position;

    SPointLight(CColor i, Point p)
    {
        intensity = i;
        position = p;
    }

    bool operator==(const SPointLight& other) const;
};

CColor Lighting(CMaterial m, Shape_ptr object, SPointLight light, Point position, Vector eye_v, Vector normal_v, bool in_shadow);

#endif //CPP_RAYTRACER_LIGHT_H
