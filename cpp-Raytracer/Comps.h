//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_COMP_H
#define CPP_RAYTRACER_COMP_H

#endif //CPP_RAYTRACER_COMP_H

#include "Sphere.h"

//Data structure to hold precalculated Computations about an Intersection
struct Comps {
    Sphere object;
    Point point;
    Vector eye_v;
    Vector normal_v;

    Comps(Sphere object, Point point, Vector eye_v, Vector normal_v):
            object(object),
            point(point),
            eye_v(eye_v),
            normal_v(normal_v)
    {

    }
};