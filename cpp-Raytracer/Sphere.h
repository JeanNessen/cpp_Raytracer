#pragma once
#include "Math.h"
class Sphere
{
public:
	Sphere(const int id);

	const int id;

	Matrix4 GetTransform();
	void SetTransform(Matrix4 transform);

	bool operator==(const Sphere& other) const;
	bool operator!=(const Sphere& other) const;

private:
	Matrix4 transform = Math::identiy_matrix;
};

