#include "Sphere.h"
// Static Variables
int Sphere::latest_id = 0;

Sphere::Sphere()
{
    this->id = ++latest_id;
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
	if (other.material == this->material && other.transform == this->transform && other.id == this->id)
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
    Point object_point{transform.Inversed() * world_point};

    //Calculate Object Space normals
    Vector object_normal{object_point - Point(0, 0, 0)};

    //Convert Object Space normals to World Space
    Vector world_normal{transform.Inversed().Transposed() * object_normal};
    world_normal.w = 0;

    return world_normal.normalized();
}

Material& Sphere::GetMaterial() {
    return material;
}

void Sphere::SetMaterial(Material mat) {
    material = mat;
}


