#pragma once

#include "Math.h"
#include "CSphere.h"
#include "CPlane.h"

#include <vector>

//Forward Declarations
struct SIntersection;

class CRay
{
//Methods
private:
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

    std::vector<SIntersection> LocalIntersect(Sphere_ptr s);
    std::vector<SIntersection> LocalIntersect(Plane_ptr p);

//Members
private:
public:
    const Point origin;
    const Vector direction;
};


