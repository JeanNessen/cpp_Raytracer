#pragma once

#include "Math.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Comps.h"
#include <vector>
#include <initializer_list>

//Returns a std::vector of the input intersections
std::vector<Intersection> Intersections(std::initializer_list<Intersection> args);

//Returns the closest not negative intersection
Intersection* Hit(std::vector<Intersection> &intersections);

class Ray
{
public:
	Ray(Point origin, Vector direction);

	//Returns the position of the Ray at the given distance from the origin
	Point Position(float distance);

	//Returns the distances at which the Ray intersects the given sphere
    //Returns empty vector if no intersection
    //Returns std::vector of length 2 on any kind of intersection
	std::vector<Intersection> Intersect(Sphere s);

	//Transforms the Ray according to the given transformation Matrix
	Ray Transform(Matrix4 matrix);

	Comps PrepareComputations(Intersection i);

	const Point origin;
	const Vector direction;



private:

};


