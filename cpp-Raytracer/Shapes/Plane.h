//
// Created by Jean-Luc von Nessen on 22.02.22.
//
#pragma once

#include "Shape.h"


class Plane: public Shape {
//Methods
public:
    Plane();

    Vector LocalNormalAt(Point local_point) const override;
};

using Plane_ptr = std::shared_ptr<Plane>;

