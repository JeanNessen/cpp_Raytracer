#pragma once

#include <vector>
#include "shape.h"



class Sphere: public shape
{
public:
	explicit Sphere();

	[[nodiscard]] vector local_normal_at(point pLocalPoint) const override;
};

using sphere_ptr = std::shared_ptr<Sphere>;
