//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#ifndef CPP_RAYTRACER_LIGHT_H
#define CPP_RAYTRACER_LIGHT_H

#include "Color.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"

struct PointLight{
    Color intensity{};
    Point position;

    PointLight(Color i, Point p)
    {
        intensity = i;
        position = p;
    }

    bool operator==(const PointLight& other) const;
};

Color Lighting(Material m, Shape_ptr object, PointLight light, Point position, Vector eye_v, Vector normal_v, bool in_shadow);

#endif //CPP_RAYTRACER_LIGHT_H
