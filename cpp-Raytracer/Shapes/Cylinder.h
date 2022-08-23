#pragma once

#include "shape.h"

class cylinder final : public shape
{
public:
	cylinder();

	[[nodiscard]] Vector local_normal_at(Point pLocalPoint) const override;

public:
	double minimum = -std::numeric_limits<double>::infinity();
	double maximum = std::numeric_limits<double>::infinity();

	bool closed = false;
private:

};


using cylinder_ptr = std::shared_ptr<cylinder>;