//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#pragma once

#include "color.h"
#include "Material.h"
#include "Math.h"
#include "Shapes/shape.h"

struct point_light{
    color intensity{};
    point position;

    point_light(color i, point p)
    {
        intensity = i;
        position = p;
    }

    bool operator==(const point_light& other) const;
};

color Lighting(material m, shape_ptr object, point_light light, point position, vector eye_v, vector normal_v, bool in_shadow);

