//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_INTERSECTION_H
#define CPP_RAYTRACER_INTERSECTION_H

#include "Ray.h"


class Intersection {

public:
    //Distance at which the intersection took place, along the given ray
    float t{};
    Sphere object; //needs to be another class, only spheres for now

    bool operator==(const Intersection& other) const;

};

#endif //CPP_RAYTRACER_INTERSECTION_H
