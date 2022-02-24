#pragma once

#include <vector>
#include "Shape.h"

class Sphere: public Shape
{
public:
	explicit Sphere();

    Vector LocalNormalAt(Point local_point) const override;
};

