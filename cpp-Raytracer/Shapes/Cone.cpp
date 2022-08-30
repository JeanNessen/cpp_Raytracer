#include "Cone.h"

cone::cone():
	shape(shape_type::cone)
{

}

Vector cone::local_normal_at(point pLocalPoint) const
{
	const double distance{ std::pow(pLocalPoint.x, 2) + std::pow(pLocalPoint.z, 2) };

	if (distance < 1 && pLocalPoint.y >= maximum - EPSILON)
	{
		return { 0, 1, 0 };
	}

	if (distance < 1 && pLocalPoint.y <= minimum + EPSILON)
	{
		return { 0, -1, 0 };
	}

	double y{ std::sqrt(std::pow(pLocalPoint.x, 2) + std::pow(pLocalPoint.z, 2)) };
	if (pLocalPoint.y > 0)
	{
		y = -y;
	}

	return{ pLocalPoint.x, y, pLocalPoint.z };
}
