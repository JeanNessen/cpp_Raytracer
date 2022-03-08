//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#pragma once
#include "CSphere.h"
#include "CPlane.h"
#include <vector>

struct SIntersection {

public:
    //Distance at which the intersection took place, along the given ray
    double t{};

    //The object with which this intersection occurred
    const Shape_ptr object;

    bool operator==(const SIntersection& other) const;

    SIntersection(double t, Shape_ptr  shape);

};

//Returns the closest not negative intersection
SIntersection* Hit(std::vector<SIntersection> &intersections);

