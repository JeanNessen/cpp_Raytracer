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

Vector Sphere::NormalAt(Point world_point) {
    //Convert point from World Space to Object Space
    Tuple object_tuple = transform.Inversed() * world_point;
    Point object_point{object_tuple.x, object_tuple.y, object_tuple.z};

    //Calculate Object Space normals
    Tuple object_normal_t = object_point - Point(0, 0, 0);
    Vector object_normal{object_normal_t.x, object_normal_t.y, object_normal_t.z};

    //Convert Object Space normals to World Space
    Tuple world_normal_t = transform.Inversed().Transposed() * object_normal;
    Vector world_normal{world_normal_t.x, world_normal_t.y, world_normal_t.z};
    world_normal.w = 0;

    return world_normal.normalized();
}
