//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_INTERSECTION_H
#define CPP_RAYTRACER_INTERSECTION_H

#include "Shape.h"
#include <vector>

class Intersection {

public:
    //Distance at which the intersection took place, along the given ray
    double t{};

    //The object with which this intersection occurred
    Shape object;

    bool operator==(const Intersection& other) const;

};

//Returns a std::vector of the input intersections
std::vector<Intersection> Intersections(std::initializer_list<Intersection> args);

//Returns the closest not negative intersection
Intersection* Hit(std::vector<Intersection> &intersections);

#endif //CPP_RAYTRACER_INTERSECTION_H
