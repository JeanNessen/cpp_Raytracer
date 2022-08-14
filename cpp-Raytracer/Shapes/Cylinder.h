#pragma once

#include "Shape.h"

class Cylinder: public Shape
{
public:
	Cylinder();

	Vector LocalNormalAt(Point local_point) const override;

public:
	double minimum = -std::numeric_limits<double>::infinity();
	double maximum = std::numeric_limits<double>::infinity();

	bool closed = false;
private:

};


using Cylinder_ptr = std::shared_ptr<Cylinder>;