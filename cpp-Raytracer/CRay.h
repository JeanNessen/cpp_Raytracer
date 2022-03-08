#pragma once

#include "Math.h"
#include "CSphere.h"
#include "CPlane.h"

#include "SIntersection.h"
#include <vector>
#include <initializer_list>



class CRay
{
public:
	CRay(Point origin, Vector direction);

	//Returns the position of the CRay at the given distance from the origin
	Point Position(double distance);

	//Returns the distances at which the CRay intersects the given sphere
    //Returns empty vector if no intersection
    //Returns std::vector of length 2 on any kind of intersection
    std::vector<SIntersection> Intersect(Shape_ptr s);

	//Transforms the CRay according to the given transformation Matrix
	CRay Transform(Matrix4 matrix);


	const Point origin;
	const Vector direction;

    std::vector<SIntersection> LocalIntersect(Sphere_ptr s);
    std::vector<SIntersection> LocalIntersect(Plane_ptr p);

private:


};


