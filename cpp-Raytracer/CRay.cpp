#include "CRay.h"

#include "SIntersection.h"

CRay::CRay(Point origin, Vector direction):
	origin(origin),
	direction(direction)
{

}

Point CRay::Position(double distance)
{
	Tuple distance_travelled = direction * distance;
	Point position{ distance_travelled.x + origin.x,
					distance_travelled.y + origin.y,
					distance_travelled.z + origin.z };
	return position;
}

CRay CRay::Transform(Matrix4 matrix)
{
	Tuple origin_tuple{ matrix * origin };
	Tuple direction_tuple{ matrix * direction };

	Point origin{ origin_tuple.x, origin_tuple.y, origin_tuple.z };
	Vector direction{ direction_tuple.x, direction_tuple.y, direction_tuple.z };

	CRay r = CRay{origin, direction };
	return r;
}

std::vector<SIntersection> CRay::Intersect(Shape_ptr s) {

    //Transform the CRay before calculating intersections, to account for the m_transform of the intersected sphere
    CRay local_ray{Transform(s->GetTransform().Inversed()) };

    s->saved_ray_direction = local_ray.direction;
    s->saved_ray_origin = local_ray.origin;


    switch (s->type) {
        case CShape::EShapeType::sphere:
            return local_ray.LocalIntersect(std::dynamic_pointer_cast<CSphere>(s));
        case CShape::EShapeType::plane:
            return local_ray.LocalIntersect(std::dynamic_pointer_cast<CPlane>(s));
        case CShape::EShapeType::cube:
            return local_ray.LocalIntersect(std::dynamic_pointer_cast<CCube>(s));
    }
}

std::vector<SIntersection> CRay::LocalIntersect(Sphere_ptr s) {
    Tuple sphere_to_ray_tmp = origin - Point(0, 0, 0); //vector from the center of the sphere to the ray origin
    Vector sphere_to_ray{ sphere_to_ray_tmp.x, sphere_to_ray_tmp.y, sphere_to_ray_tmp.z };

    double a = Math::Dot(direction, direction);
    double b = 2 * Math::Dot(direction, sphere_to_ray);
    double c = Math::Dot(sphere_to_ray, sphere_to_ray) - 1;

    double discriminant = std::pow(b, 2) - 4 * a * c;

    //If the discriminant is smaller than 0, the ray does not intersect the sphere
    if (discriminant < 0 )
    {
        return {};
    }

    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    SIntersection i1{t1, s };
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    SIntersection i2{t2, s };
    return std::vector<SIntersection>{i1, i2};
}

std::vector<SIntersection> CRay::LocalIntersect(Plane_ptr p) {
    if(std::abs(direction.y) < EPSILON)
    {
        return{};
    } else
    {
        double t{-origin.y / direction.y};
        return std::vector<SIntersection>{SIntersection(t, p)};
    }
}

std::vector<SIntersection> CRay::LocalIntersect(Cube_ptr c) {
    //Find the minimum and maximum intersections for the ray with each of the axes
    std::vector<double> x_tmin_tmax = CheckAxis(origin.x, direction.x);
    std::vector<double> y_tmin_tmax = CheckAxis(origin.y, direction.y);
    std::vector<double> z_tmin_tmax = CheckAxis(origin.z, direction.z);

    double tmin = std::max({x_tmin_tmax[0], y_tmin_tmax[0], z_tmin_tmax[0]});
    double tmax = std::min({x_tmin_tmax[1], y_tmin_tmax[1], z_tmin_tmax[1]});

    if (tmin > tmax)
    //The Ray misses the Cube
    {
        return {};
    }

    return {SIntersection(tmin, c), SIntersection(tmax, c)};
}

std::vector<double> CRay::CheckAxis(double axis_origin, double axis_direction)
{
    double tmin_enumerator{-1 - axis_origin};
    double tmax_enumerator{1 - axis_origin};
    double tmin;
    double tmax;

    if (abs(axis_direction) >= EPSILON)
    {
        tmin = tmin_enumerator / axis_direction;
        tmax = tmax_enumerator / axis_direction;
    }
    else
    {
        tmin = tmin_enumerator * INFINITY;
        tmax = tmax_enumerator * INFINITY;
    }

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    return {tmin, tmax};
}



