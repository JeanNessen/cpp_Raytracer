//
// Created by Jean-Luc von Nessen on 13.03.22.
//
#pragma once

#include "CShape.h"


class CCube: public CShape {
//Methods
private:
public:
    CCube();

    Vector LocalNormalAt(Point local_point) const override;

};

using Cube_ptr = std::shared_ptr<CCube>;
