//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#pragma once
#include "Shapes/Shape.h"
#include <vector>

struct Intersection {

public:
    //Distance at which the intersection took place, along the given ray
    double t{};

    //The object with which this intersection occurred
    const Shape_ptr object;

    bool operator==(const Intersection& other) const;

    Intersection(double t, Shape_ptr  shape);

};

//Returns the closest not negative intersection
Intersection* Hit(std::vector<Intersection> &intersections);

