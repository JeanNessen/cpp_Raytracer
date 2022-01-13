//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#ifndef CPP_RAYTRACER_LIGHT_H
#define CPP_RAYTRACER_LIGHT_H

#include "Color.h"
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


#endif //CPP_RAYTRACER_LIGHT_H
