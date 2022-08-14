#pragma once

#include "Shape.h"

class Cone: public Shape
{
public:
	Cone();

	[[nodiscard]] Vector LocalNormalAt(Point local_point) const override;

	double minimum = -std::numeric_limits<double>::infinity();
	double maximum = std::numeric_limits<double>::infinity();

	bool closed = false;
private:

};

using Cone_ptr = std::shared_ptr<Cone>;