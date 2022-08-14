//
// Created by Jean-Luc von Nessen on 13.03.22.
//
#pragma once

#include "Shape.h"


class Cube: public Shape {
//Methods
private:
public:
    Cube();

[[nodiscard]] Vector LocalNormalAt(Point local_point) const override;

};

using Cube_ptr = std::shared_ptr<Cube>;
