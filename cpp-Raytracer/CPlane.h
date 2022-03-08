//
// Created by Jean-Luc von Nessen on 22.02.22.
//
#pragma once

#include "CShape.h"


class CPlane: public CShape {

public:
    CPlane();

    Vector LocalNormalAt(Point local_point) const override;
};

using Plane_ptr = std::shared_ptr<CPlane>;

