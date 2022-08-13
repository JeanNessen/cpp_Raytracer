#include "Cylinder.h"


Cylinder::Cylinder():
		Shape(EShapeType::cylinder)
{

}

Vector Cylinder::LocalNormalAt(Point local_point) const
{
	double distance{ std::pow(local_point.x, 2) + std::pow(local_point.z, 2) };

	if(distance < 1 && local_point.y >= maximum - EPSILON)
	{
		return { 0, 1, 0 };
	}

	if(distance < 1 && local_point.y <= minimum + EPSILON)
	{
		return { 0, -1, 0 };
	}

	return{ local_point.x, 0, local_point.z };
}
