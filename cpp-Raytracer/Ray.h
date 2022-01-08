#pragma once

#include "Math.h"
#include "Sphere.h"
#include <vector>
#include <initializer_list>

struct Intersection
{
	float t;
	Sphere object; //needs to be another class, only spheres for now
	

	bool operator==(const Intersection& other) const;

};

std::vector<Intersection> Intersections(std::initializer_list<Intersection> args);

Intersection* Hit(std::vector<Intersection> &intersections);



class Ray
{
public:
	Ray(Point origin, Vector direction);

	//Returns the position of the Ray at the given distance from the origin
	Point Position(float distance);

	//Returns the distances at which the Ray intersects the given sphere, returns empty vector if no intersection
	std::vector<Intersection> Intersect(Sphere s);

	//Transforms the Ray according to the given transformation Matrix
	Ray Transform(Matrix4 matrix);

	

	const Point origin;
	const Vector direction;



private:

};


