#pragma once

#include "Math.h"
#include "Shapes/Sphere.h"
#include "Shapes/Plane.h"
#include "Shapes/Cube.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Cone.h"

#include <vector>




//Forward Declarations
struct intersection;


class ray
{
//Methods
private:
    //returns a vector with two doubles, tmin and tmax
    static std::vector<double> check_axis(double axis_origin, double axis_direction);
public:
	ray(point origin, vector direction);

	//Returns the position of the Ray at the given distance from the origin
	point position(double distance) const;

	//Returns the distances at which the Ray intersects the given sphere
    //Returns empty vector if no intersection
    //Returns std::vector of length 2 on any kind of intersection
    std::vector<intersection> intersect(shape_ptr s) const;

	//Transforms the Ray according to the given transformation Matrix
	ray transform(matrix4 matrix) const;

    std::vector<intersection> local_intersect(sphere_ptr s) const;
    std::vector<intersection> local_intersect(plane_ptr p) const;
    std::vector<intersection> local_intersect(cube_ptr c) const;
    std::vector<intersection> local_intersect(cylinder_ptr cylinder)const;
    std::vector<intersection> local_intersect(cone_ptr cone) const;

    //methods for intersecting cylinders and cones
	[[nodiscard]] bool check_cap(double t, double radius = 1) const;
    void intersect_caps(cylinder_ptr cylinder, std::vector<intersection>& xs) const;
    void intersect_caps(cone_ptr cone, std::vector<intersection>& xs) const;

//Members
private:
public:
    const point origin;
    const vector direction;
};


