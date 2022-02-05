#include "Ray.h"

#include <utility>
#include <algorithm>

Ray::Ray(Point origin, Vector direction):
	origin(origin),
	direction(direction)
{

}

Point Ray::Position(float distance)
{
	Tuple distance_travelled = direction * distance;
	Point position{ distance_travelled.x + origin.x,
					distance_travelled.y + origin.y,
					distance_travelled.z + origin.z };
	return position;
}

std::vector<Intersection> Ray::Intersect(Sphere s)
{
	//Transform the Ray before calculating intersections, to account for the transform of the intersected sphere
	Ray transformed_ray{ Transform(s.GetTransform().Inversed()) };

	Tuple sphere_to_ray_tmp = transformed_ray.origin - Point(0, 0, 0); //vector from the center of the sphere to the ray origin
	Vector sphere_to_ray{ sphere_to_ray_tmp.x, sphere_to_ray_tmp.y, sphere_to_ray_tmp.z };



	float a = Math::Dot(transformed_ray.direction, transformed_ray.direction);
	float b = 2 * Math::Dot(transformed_ray.direction, sphere_to_ray);
	float c = Math::Dot(sphere_to_ray, sphere_to_ray) - 1;

	float discriminant = std::pow(b, 2) - 4 * a * c;

	//If the discriminant is smaller than 0, the ray does not intersect the sphere
	if (discriminant < 0 ) 
	{
		return std::vector<Intersection>();
	}

	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	Intersection i1{ t1, s };
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	Intersection i2{ t2, s };
	return std::vector<Intersection>{i1, i2};
}

Ray Ray::Transform(Matrix4 matrix)
{
	Tuple origin_tuple{ matrix * origin };
	Tuple direction_tuple{ matrix * direction };

	Point origin{ origin_tuple.x, origin_tuple.y, origin_tuple.z };
	Vector direction{ direction_tuple.x, direction_tuple.y, direction_tuple.z };

	Ray r = Ray{ origin, direction };
	return r;
}

Comps Ray::PrepareComputations(Intersection i) {

    return Comps();
}

std::vector<Intersection> Intersections(std::initializer_list<Intersection> args)
{
	std::vector<Intersection> intersections;

	for (auto i : args)
	{
		intersections.push_back(i);
	}

	return intersections;
}

Intersection* Hit(std::vector<Intersection> &intersections)
{
	Intersection *hit = nullptr;
	for (int i = 0; i < intersections.size(); i++)
	{
		if (intersections[i].t < 0)
		{
			continue;
		}
		if (hit == nullptr)
		{
			hit = &intersections[i];
		}
		else if (intersections[i].t < hit->t)
		{
			hit = &intersections[i];
		}
	}
	return hit;
}


