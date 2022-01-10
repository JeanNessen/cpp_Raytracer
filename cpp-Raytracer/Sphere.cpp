#include "Sphere.h"

Sphere::Sphere(const int id):
	id(id)
{

}

Matrix4 Sphere::GetTransform()
{
	return transform;
}

void Sphere::SetTransform(Matrix4 transform)
{
	this->transform = transform;
}

bool Sphere::operator==(const Sphere& other) const
{
	if (other.id == this->id)
	{
		return true;
	}
	return false;
}

bool Sphere::operator!=(const Sphere& other) const
{
	return !(*this == other);
}

Vector Sphere::NormalAt(Point p) {
    Tuple normal_t = p - Point(0, 0, 0);
    Vector normal{normal_t.x, normal_t.y, normal_t.z};
    return normal.normalized();
}
