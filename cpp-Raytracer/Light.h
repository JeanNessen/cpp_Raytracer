//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#pragma once

#include "color.h"
#include "Material.h"
#include "Math.h"
#include "Shapes/shape.h"

struct PointLight{
    color intensity{};
    Point position;

    PointLight(color i, Point p)
    {
        intensity = i;
        position = p;
    }

    bool operator==(const PointLight& other) const;
};

color Lighting(Material m, shape_ptr object, PointLight light, Point position, Vector eye_v, Vector normal_v, bool in_shadow);

