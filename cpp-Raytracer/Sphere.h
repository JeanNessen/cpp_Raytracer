#pragma once
#include "Math.h"
#include "Material.h"

class Sphere
{
public:
	explicit Sphere(int id);

	int id;

	Matrix4 GetTransform();
	void SetTransform(Matrix4 transform);

    Material& GetMaterial();
    void SetMaterial(Material mat);

    //Returns the World Normal of a point on the Sphere
    Vector NormalAt(Point world_point);

	bool operator==(const Sphere& other) const;
	bool operator!=(const Sphere& other) const;

private:
	Matrix4 transform = Math::identiy_matrix;
    Material material{};
};

