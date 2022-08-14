#include "Cone.h"

Cone::Cone():
	Shape(EShapeType::cone)
{

}

Vector Cone::LocalNormalAt(Point local_point) const
{
	double distance{ std::pow(local_point.x, 2) + std::pow(local_point.z, 2) };

	if (distance < 1 && local_point.y >= maximum - EPSILON)
	{
		return { 0, 1, 0 };
	}

	if (distance < 1 && local_point.y <= minimum + EPSILON)
	{
		return { 0, -1, 0 };
	}

	double y{ std::sqrt(std::pow(local_point.x, 2) + std::pow(local_point.z, 2)) };
	if (local_point.y > 0)
	{
		y = -y;
	}

	return{ local_point.x, y, local_point.z };
}
