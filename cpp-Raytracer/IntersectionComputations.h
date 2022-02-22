//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_COMP_H
#define CPP_RAYTRACER_COMP_H

#endif //CPP_RAYTRACER_COMP_H

#include "Sphere.h"

//Data structure to hold precalculated Computations about an Intersection
struct IntersectionComputations {
    double t;
    Sphere object;
    Point point;
    Vector eye_v;
    Vector normal_v;
    bool inside;
    Point over_point;

    IntersectionComputations(double t, Sphere object, Point point, Vector eye_v, Vector normal_v):
            t(t),
            object(object),
            point(point),
            eye_v(eye_v),
            normal_v(normal_v)
    {
        if(Math::Dot(normal_v, eye_v) < 0)
        {
            //The hit occurred inside the object, invert the normal
            inside = true;
            this->normal_v.x = -normal_v.x;
            this->normal_v.y = -normal_v.y;
            this->normal_v.z = -normal_v.z;
        }
        else
        {
            inside = false;
        }
        over_point = Point{this->point + this->normal_v * 0.00001};
    }
};