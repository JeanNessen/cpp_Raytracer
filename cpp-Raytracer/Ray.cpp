#include "Ray.h"
#include <algorithm>

#include "Intersection.h"

ray::ray(const point origin, const vector direction):
	origin(origin),
	direction(direction)
{

}

point ray::position(const double distance) const
{
	const tuple distanceTraveled = direction * distance;
	const point position{ distanceTraveled.x + origin.x,
					distanceTraveled.y + origin.y,
					distanceTraveled.z + origin.z };
	return position;
}

ray ray::transform(const matrix4 matrix) const
{
	const tuple originTuple{ matrix * origin };
	const tuple directionTuple{ matrix * direction };

	const point newOrigin{ originTuple.x, originTuple.y, originTuple.z };
	const vector newDirection{ directionTuple.x, directionTuple.y, directionTuple.z };

	ray r = ray{newOrigin, newDirection };
	return r;
}

std::vector<intersection> ray::intersect(shape_ptr s) const
{

    //Transform the Ray before calculating intersections, to account for the m_transform of the intersected sphere
    const ray localRay{transform(s->get_transform().Inversed()) };

    s->saved_ray_direction = localRay.direction;
    s->saved_ray_origin = localRay.origin;


    switch (s->type) {
        case shape::shape_type::sphere:
            return localRay.local_intersect(std::dynamic_pointer_cast<Sphere>(s));
        case shape::shape_type::plane:
            return localRay.local_intersect(std::dynamic_pointer_cast<plane>(s));
        case shape::shape_type::cube:
            return localRay.local_intersect(std::dynamic_pointer_cast<cube>(s));
		case shape::shape_type::cylinder:
			return localRay.local_intersect(std::dynamic_pointer_cast<cylinder>(s));
		case shape::shape_type::cone:
            return localRay.local_intersect(std::dynamic_pointer_cast<cone>(s));
		default:
			std::cout << "Shape not recognized in intersection.\n";
    		return {};
    }
}

std::vector<intersection> ray::local_intersect(sphere_ptr s) const
{
	const tuple sphereToRayTmp = origin - point(0, 0, 0); //vector from the center of the sphere to the ray origin
	const vector sphereToRay{ sphereToRayTmp.x, sphereToRayTmp.y, sphereToRayTmp.z };

	const double a = Math::Dot(direction, direction);
	const double b = 2 * Math::Dot(direction, sphereToRay);
	const double c = Math::Dot(sphereToRay, sphereToRay) - 1;

	const double discriminant = std::pow(b, 2) - 4 * a * c;

    //If the discriminant is smaller than 0, the ray does not intersect the sphere
    if (discriminant < 0 )
    {
        return {};
    }

	const double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	const intersection i1{t1, s };
	const double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	const intersection i2{t2, s };
    return std::vector<intersection>{i1, i2};
}

std::vector<intersection> ray::local_intersect(plane_ptr p) const
{
    if(std::abs(direction.y) < EPSILON)
    {
        return{};
    } else
    {
        double t{-origin.y / direction.y};
        return std::vector<intersection>{intersection(t, p)};
    }
}

std::vector<intersection> ray::local_intersect(cube_ptr c) const
{
    //Find the minimum and maximum intersections for the ray with each of the axes
    std::vector<double> xTminTmax = check_axis(origin.x, direction.x);
    std::vector<double> yTminTmax = check_axis(origin.y, direction.y);
    std::vector<double> zTminTmax = check_axis(origin.z, direction.z);

    double tmin = std::max({xTminTmax[0], yTminTmax[0], zTminTmax[0]});
    double tmax = std::min({xTminTmax[1], yTminTmax[1], zTminTmax[1]});

    if (tmin > tmax)
    //The Ray misses the Cube
    {
        return std::vector<intersection>{};
    }

    return std::vector<intersection>{intersection(tmin, c), intersection(tmax, c)};
}

std::vector<intersection> ray::local_intersect(cylinder_ptr cylinder) const
{
    double a = std::pow(direction.x, 2) + std::pow(direction.z, 2);

    //Ray is parallel to the y axis
    if(Math::Equal(a, 0))
    {
        std::vector<intersection> xs;
        intersect_caps(cylinder, xs);
        return xs;
    }

    double b = 2 * origin.x * direction.x + 2 * origin.z * direction.z;
    double c = std::pow(origin.x, 2) + std::pow(origin.z, 2) - 1;

    double discriminant = std::pow(b, 2) - 4 * a * c;

    //Ray does not intersect the cylinder
    if(discriminant < 0)
    {
        return{};
    }

    //Actual intersection
    double t0{ (-b - std::sqrt(discriminant)) / (2 * a) };
    double t1{ (-b + std::sqrt(discriminant)) / (2 * a) };
    if(t0 > t1)
    {
        const double temp{ t0 };
        t0 = t1;
        t1 = temp;
    }

    std::vector<intersection> xs{};

    const double y0{ origin.y + t0 * direction.y };
    if(cylinder->minimum < y0 && y0 < cylinder->maximum)
    {
        xs.emplace_back(t0, cylinder);
    }

    const double y1{ origin.y + t1 * direction.y };
    if(cylinder->minimum < y1 && y1 < cylinder->maximum)
    {
        xs.emplace_back(t1, cylinder);
    }

    intersect_caps(cylinder, xs);

    return xs;
}

std::vector<intersection> ray::local_intersect(cone_ptr cone) const
{
    double a{ std::pow(direction.x, 2) - std::pow(direction.y, 2) + std::pow(direction.z, 2) };
    double b{ (2 * origin.x * direction.x) - (2 * origin.y * direction.y) + (2 * origin.z * direction.z) };
    double c{ std::pow(origin.x, 2) - std::pow(origin.y, 2) + std::pow(origin.z, 2) };

    //Ray misses if both a and b are equal
    if(Math::Equal(a, 0) && Math::Equal(b, 0))
    {
        return{};
    }
    if(Math::Equal(a, 0) && !Math::Equal(b, 0))
    {
        double t{ -c / (2 * b) };
        std::vector<intersection> xs{ {t, cone} };

        intersect_caps(cone, xs);

        return xs;
    }

    double discriminant = std::pow(b, 2) - 4 * a * c;

    //Ray does not intersect the cylinder
    if (discriminant < 0)
    {
        return{};
    }

    //Actual intersection
    double t0{ (-b - std::sqrt(discriminant)) / (2 * a) };
    double t1{ (-b + std::sqrt(discriminant)) / (2 * a) };
    if (t0 > t1)
    {
        const double temp{ t0 };
        t0 = t1;
        t1 = temp;
    }

    std::vector<intersection> xs{};

    const double y0{ origin.y + t0 * direction.y };
    if (cone->minimum < y0 && y0 < cone->maximum)
    {
        xs.emplace_back(t0, cone);
    }

    const double y1{ origin.y + t1 * direction.y };
    if (cone->minimum < y1 && y1 < cone->maximum)
    {
        xs.emplace_back(t1, cone);
    }

    intersect_caps(cone, xs);

    return xs;
}

bool ray::check_cap(const double t, const double radius) const
{
    double x{ origin.x + t * direction.x };
    double z{ origin.z + t * direction.z };

    return (std::pow(x, 2) + std::pow(z, 2)) <= std::abs(radius);
}

void ray::intersect_caps(cylinder_ptr cylinder, std::vector<intersection>& xs) const
{
    //Caps only matter if the cylinder is closed, and might possibly be intersected by the ray
    if(!cylinder->closed || Math::Equal(direction.y, 0))
    {
        return;
    }

    //Check for an intersection with the lower end cap by intersection the ray with the plane at y = cylinder.minimum
    double t{ (cylinder->minimum - origin.y) / direction.y };
    if(check_cap(t))
    {
        xs.emplace_back(t, cylinder);
    }

    //Check for an intersection with the upper end cap by intersection the ray with the plane at y = cylinder.maximum
    t = (cylinder->maximum - origin.y) / direction.y;
    if(check_cap(t))
    {
        xs.emplace_back(t, cylinder);
    }
}

void ray::intersect_caps(cone_ptr cone, std::vector<intersection>& xs) const
{
    //Caps only matter if the cylinder is closed, and might possibly be intersected by the ray
    if (!cone->closed || Math::Equal(direction.y, 0))
    {
        return;
    }

    //Check for an intersection with the lower end cap by intersection the ray with the plane at y = cylinder.minimum
    double t{ (cone->minimum - origin.y) / direction.y };
    if (check_cap(t, cone->minimum))
    {
        xs.emplace_back(t, cone);
    }

    //Check for an intersection with the upper end cap by intersection the ray with the plane at y = cylinder.maximum
    t = (cone->maximum - origin.y) / direction.y;
    if (check_cap(t, cone->maximum))
    {
        xs.emplace_back(t, cone);
    }
}

std::vector<double> ray::check_axis(const double axis_origin, const double axis_direction)
{
	const double tMinEnumerator{-1 - axis_origin};
	const double tMaxEnumerator{1 - axis_origin};
    double tMin;
    double tMax;

    if (std::abs(axis_direction) >= EPSILON)
    {
        tMin = tMinEnumerator / axis_direction;
        tMax = tMaxEnumerator / axis_direction;
    }
    else
    {
        tMin = tMinEnumerator * INFINITY;
        tMax = tMaxEnumerator * INFINITY;
    }

    if (tMin > tMax)
    {
        std::swap(tMin, tMax);
    }

    return std::vector<double>{tMin, tMax};
}



