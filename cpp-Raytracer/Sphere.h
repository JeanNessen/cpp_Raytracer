#pragma once

#include <vector>
#include "Shape.h"

class Sphere: public Shape
{
public:
	explicit Sphere();

    //Returns the World Normal of a point on the Sphere
    Vector NormalAt(Point world_point);

};

