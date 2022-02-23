#include "Ray.h"

#include <utility>
#include <algorithm>

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

	Ray r = Ray{ origin, direction };
	return r;
}

//IntersectionComputations Ray::PrepareComputations(Intersection i) {
//    //Copy intersection properties for convenience
//    double comps_t{i.t};
//    Sphere comps_object{i.object};
//
//    //precompute needed values
//    Point comps_point{Position(i.t)};
//    Vector comps_eye_v{-direction.x, -direction.y, -direction.z};
//    Vector comps_normal_v{i.object.NormalAt(Position(i.t))};
//
//    IntersectionComputations comps{
//            comps_t,
//            comps_object,
//            comps_point,
//            comps_eye_v,
//            comps_normal_v
//    };
//
//    return comps;
//}

std::vector<Intersection> Ray::Intersect(Shape& s) {

    //Transform the Ray before calculating intersections, to account for the transform of the intersected sphere
    Ray local_ray{ Transform(s.GetTransform().Inversed()) };

    s.saved_ray_direction = local_ray.direction;
    s.saved_ray_origin = local_ray.origin;


    switch (s.type) {
        case ShapeType::sphere:
            return local_ray.LocalIntersect(dynamic_cast<Sphere&>(s));
        case ShapeType::plane:
            return local_ray.LocalIntersect(dynamic_cast<Plane&>(s));
    }
}

std::vector<Intersection> Ray::LocalIntersect(Sphere& s) {
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
    Intersection i1{ t1, s };
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    Intersection i2{ t2, s };
    return std::vector<Intersection>{i1, i2};
}

std::vector<Intersection> Ray::LocalIntersect(Plane& p) {
    return std::vector<Intersection>();
}




