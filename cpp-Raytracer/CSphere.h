#pragma once

#include <vector>
#include "CShape.h"



class CSphere: public CShape
{
public:
	explicit CSphere();

    Vector LocalNormalAt(Point local_point) const override;
};

using Sphere_ptr = std::shared_ptr<CSphere>;
