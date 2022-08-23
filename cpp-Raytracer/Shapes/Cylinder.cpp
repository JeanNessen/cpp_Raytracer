#include "Cylinder.h"


cylinder::cylinder():
		shape(shape_type::cylinder)
{

}

Vector cylinder::local_normal_at(Point pLocalPoint) const
{
	const double distance{ std::pow(pLocalPoint.x, 2) + std::pow(pLocalPoint.z, 2) };

	if(distance < 1 && pLocalPoint.y >= maximum - EPSILON)
	{
		return { 0, 1, 0 };
	}

	if(distance < 1 && pLocalPoint.y <= minimum + EPSILON)
	{
		return { 0, -1, 0 };
	}


	return{ pLocalPoint.x, 0, pLocalPoint.z };
}
