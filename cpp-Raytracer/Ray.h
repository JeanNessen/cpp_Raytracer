#pragma once

#include "Math.h"
#include "Sphere.h"
#include "Plane.h"

#include "Intersection.h"
#include <vector>
#include <initializer_list>



class Ray
{
public:
	Ray(Point origin, Vector direction);

	//Returns the position of the Ray at the given distance from the origin
	Point Position(double distance);

	//Returns the distances at which the Ray intersects the given sphere
    //Returns empty vector if no intersection
    //Returns std::vector of length 2 on any kind of intersection
    std::vector<Intersection> Intersect(Shape_ptr s);

	//Transforms the Ray according to the given transformation Matrix
	Ray Transform(Matrix4 matrix);


	const Point origin;
	const Vector direction;

    std::vector<Intersection> LocalIntersect(Sphere_ptr s);
    std::vector<Intersection> LocalIntersect(Plane_ptr p);

private:


};


