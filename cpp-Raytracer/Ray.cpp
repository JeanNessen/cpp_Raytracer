#include "Ray.h"
#include <algorithm>

#include "Intersection.h"

Ray::Ray(Point origin, Vector direction):
	origin(origin),
	direction(direction)
{

}

Point Ray::Position(double distance)
{
	Tuple distance_travelled = direction * distance;
	Point position{ distance_travelled.x + origin.x,
					distance_travelled.y + origin.y,
					distance_travelled.z + origin.z };
	return position;
}

Ray Ray::Transform(Matrix4 matrix)
{
	Tuple origin_tuple{ matrix * origin };
	Tuple direction_tuple{ matrix * direction };

	Point origin{ origin_tuple.x, origin_tuple.y, origin_tuple.z };
	Vector direction{ direction_tuple.x, direction_tuple.y, direction_tuple.z };

	Ray r = Ray{origin, direction };
	return r;
}

std::vector<Intersection> Ray::Intersect(Shape_ptr s) {

    //Transform the Ray before calculating intersections, to account for the m_transform of the intersected sphere
    Ray local_ray{Transform(s->GetTransform().Inversed()) };

    s->saved_ray_direction = local_ray.direction;
    s->saved_ray_origin = local_ray.origin;


    switch (s->type) {
        case Shape::EShapeType::sphere:
            return local_ray.local_intersect(std::dynamic_pointer_cast<Sphere>(s));
        case Shape::EShapeType::plane:
            return local_ray.local_intersect(std::dynamic_pointer_cast<Plane>(s));
        case Shape::EShapeType::cube:
            return local_ray.local_intersect(std::dynamic_pointer_cast<Cube>(s));
		case Shape::EShapeType::cylinder:
			return local_ray.local_intersect(std::dynamic_pointer_cast<Cylinder>(s));
		case Shape::EShapeType::cone:
            return local_ray.local_intersect(std::dynamic_pointer_cast<Cone>(s));
    }
}

std::vector<Intersection> Ray::local_intersect(Sphere_ptr s) {
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
    Intersection i1{t1, s };
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    Intersection i2{t2, s };
    return std::vector<Intersection>{i1, i2};
}

std::vector<Intersection> Ray::local_intersect(Plane_ptr p) {
    if(std::abs(direction.y) < EPSILON)
    {
        return{};
    } else
    {
        double t{-origin.y / direction.y};
        return std::vector<Intersection>{Intersection(t, p)};
    }
}

std::vector<Intersection> Ray::local_intersect(Cube_ptr c) {
    //Find the minimum and maximum intersections for the ray with each of the axes
    std::vector<double> x_tmin_tmax = CheckAxis(origin.x, direction.x);
    std::vector<double> y_tmin_tmax = CheckAxis(origin.y, direction.y);
    std::vector<double> z_tmin_tmax = CheckAxis(origin.z, direction.z);

    double tmin = std::max({x_tmin_tmax[0], y_tmin_tmax[0], z_tmin_tmax[0]});
    double tmax = std::min({x_tmin_tmax[1], y_tmin_tmax[1], z_tmin_tmax[1]});

    if (tmin > tmax)
    //The Ray misses the Cube
    {
        return std::vector<Intersection>{};
    }

    return std::vector<Intersection>{Intersection(tmin, c), Intersection(tmax, c)};
}

std::vector<Intersection> Ray::local_intersect(Cylinder_ptr cylinder)
{
    double a = std::pow(direction.x, 2) + std::pow(direction.z, 2);

    //Ray is parallel to the y axis
    if(Math::Equal(a, 0))
    {
        std::vector<Intersection> xs;
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

    std::vector<Intersection> xs{};

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

std::vector<Intersection> Ray::local_intersect(Cone_ptr cone)
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
        std::vector<Intersection> xs{ {t, cone} };

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

    std::vector<Intersection> xs{};

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

bool Ray::check_cap(const double t, const double radius) const
{
    double x{ origin.x + t * direction.x };
    double z{ origin.z + t * direction.z };

    return (std::pow(x, 2) + std::pow(z, 2)) <= std::abs(radius);
}

void Ray::intersect_caps(Cylinder_ptr cylinder, std::vector<Intersection>& xs)
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

void Ray::intersect_caps(Cone_ptr cone, std::vector<Intersection>& xs)
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

std::vector<double> Ray::CheckAxis(double axis_origin, double axis_direction)
{
    double tmin_enumerator{-1 - axis_origin};
    double tmax_enumerator{1 - axis_origin};
    double tmin;
    double tmax;

    if (std::abs(axis_direction) >= EPSILON)
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

    return std::vector<double>{tmin, tmax};
}



