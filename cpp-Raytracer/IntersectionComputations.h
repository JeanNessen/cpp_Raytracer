//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_COMP_H
#define CPP_RAYTRACER_COMP_H

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

//Data structure to hold precalculated Computations about an Intersection
struct IntersectionComputations {
    double t;
    const Shape& object;
    Point point;
    Vector eye_v;
    Vector normal_v;
    bool inside;
    Point over_point;

    IntersectionComputations(double t, const Shape& object, Point point, Vector eye_v, Vector normal_v);
};

IntersectionComputations PrepareComputations(Intersection intersection, Ray ray);

#endif //CPP_RAYTRACER_COMP_H

