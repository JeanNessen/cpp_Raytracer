#pragma once

#include <vector>
#include "shape.h"



class Sphere: public shape
{
public:
	explicit Sphere();

	[[nodiscard]] Vector local_normal_at(Point pLocalPoint) const override;
};

using sphere_ptr = std::shared_ptr<Sphere>;
