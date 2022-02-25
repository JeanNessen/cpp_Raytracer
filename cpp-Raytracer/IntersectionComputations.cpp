//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "IntersectionComputations.h"


IntersectionComputations::IntersectionComputations(double t, const Shape_ptr object, Point point, Vector eye_v, Vector normal_v):
        t(t),
        object(object),
        point(point),
        eye_v(eye_v),
        normal_v(normal_v)
{
    if(Math::Dot(normal_v, eye_v) < 0)
    {
        //The hit occurred inside the object, invert the normal
        inside = true;
        this->normal_v.x = -normal_v.x;
        this->normal_v.y = -normal_v.y;
        this->normal_v.z = -normal_v.z;
    }
    else
    {
        inside = false;
    }
    over_point = Point{this->point + this->normal_v * EPSILON};

}

IntersectionComputations PrepareComputations(Intersection intersection, Ray ray) {
    //Copy intersection properties for convenience
    double comps_t{intersection.t};
    const Shape_ptr comps_object{intersection.object};

    //precompute needed values
    Point comps_point{ray.Position(intersection.t)};
    Vector comps_eye_v{-ray.direction.x, -ray.direction.y, -ray.direction.z};
    Vector comps_normal_v{intersection.object->NormalAt(ray.Position(intersection.t))};

    IntersectionComputations comps{
            comps_t,
            comps_object,
            comps_point,
            comps_eye_v,
            comps_normal_v
    };

    comps.reflect_v = ray.direction.Reflect(comps_normal_v);

    return comps;
}
