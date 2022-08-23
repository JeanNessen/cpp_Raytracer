//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#pragma once
#include "Shapes/shape.h"
#include <vector>

struct intersection {

public:
    //Distance at which the intersection took place, along the given ray
    double t{};

    //The object with which this intersection occurred
    const shape_ptr object;

    bool operator==(const intersection& pOther) const;

    intersection(double pT, shape_ptr  pShape);

};

//Returns the closest not negative intersection
intersection* hit(std::vector<intersection> &pIntersections);

