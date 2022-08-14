#pragma once

#include <vector>
#include "Shape.h"



class Sphere: public Shape
{
public:
	explicit Sphere();

    Vector LocalNormalAt(Point local_point) const override;
};

using Sphere_ptr = std::shared_ptr<Sphere>;
