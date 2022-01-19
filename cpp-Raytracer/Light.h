//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#ifndef CPP_RAYTRACER_LIGHT_H
#define CPP_RAYTRACER_LIGHT_H

#include "Color.h"
#include "Material.h"
#include "Math.h"

struct PointLight{
    Color intensity{};
    Point position;

    PointLight(Color i, Point p)
    {
        intensity = i;
        position = p;
    }
};

Color Lighting(Material m, PointLight light, Point position, Vector eye_v, Vector normal_v);

#endif //CPP_RAYTRACER_LIGHT_H
