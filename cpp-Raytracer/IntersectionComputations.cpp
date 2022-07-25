//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "IntersectionComputations.h"

#include <utility>


IntersectionComputations::IntersectionComputations(double t, Shape_ptr  object, Point point, Vector eye_v, Vector normal_v, double n1, double n2):
        t(t),
        object(std::move(object)),
        point(point),
        eye_v(eye_v),
        normal_v(normal_v),
        n1(n1),
        n2(n2)
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
    under_point = Point{this->point - this->normal_v * EPSILON};

}



IntersectionComputations PrepareComputations(const Intersection& intersection, Ray ray, std::vector<Intersection> xs) {
    if(xs.empty())
    {
        xs.push_back(intersection);
    }

    //Copy intersection properties for convenience
    double comps_t {intersection.t};
    const Shape_ptr comps_object {intersection.object};

    //precompute needed values
    Point comps_point{ray.Position(intersection.t)};
    Vector comps_eye_v{-ray.direction.x, -ray.direction.y, -ray.direction.z};
    Vector comps_normal_v{intersection.object->NormalAt(ray.Position(intersection.t))};

    std::vector<double> n1_n2 = FindRefractiveIndices(intersection, xs);



    IntersectionComputations comps{
            comps_t,
            comps_object,
            comps_point,
            comps_eye_v,
            comps_normal_v,
            n1_n2[0],
            n1_n2[1]
    };

    comps.reflect_v = ray.direction.Reflect(comps_normal_v);

    return comps;
}
std::vector<double> FindRefractiveIndices(const Intersection& intersection, const std::vector<Intersection>& xs) {

    double local_n1, local_n2;

    std::vector<Shape_ptr> containers;

    //Find the refractive indices for the materials of this intersection
    for (const Intersection& i: xs) {

        //If i is the hit, n1 is the refractive index of the last object in containers, or 1 if containers is empty
        if (i == intersection)
        {
            if(containers.empty())
            {
                local_n1 = 1;
            }
            else
            {
                local_n1 = containers[containers.size()-1]->GetMaterial().refractive_index;
            }
        }

        //if containers contains i.object then the intersection is leaving the object and should be removed from the list
        auto i_obj_position = std::find(containers.begin(), containers.end(), i.object);
        if(i_obj_position != containers.end())
        {
            containers.erase(i_obj_position);
        }
        else
        {
            containers.push_back(i.object);
        }

        if(i == intersection)
        {
            if(containers.empty())
            {
                local_n2 = 1;
            }
            else
            {
                local_n2 = containers[containers.size()-1]->GetMaterial().refractive_index;
            }
            break;
        }
    }

    return std::vector<double>{local_n1, local_n2};
}

double Schlick(const IntersectionComputations& comps) {
    //Find the cosine of the angle between the eye and normal vector
    double cos = Math::Dot(comps.eye_v, comps.normal_v);

    //Total internal reflection can only occur if n1 > n2
    if(comps.n1 > comps.n2)
    {
        double n = comps.n1 / comps.n2;
        double sin2_t = std::pow(n, 2) * (1 - std::pow(cos, 2));
        if(sin2_t > 1)
        {
            return 1;
        }
        //compute the cosine of theta_t using trig identity
        double cos_t = sqrt(1 - sin2_t);

        //when n1 > n2, use cos(theta_t instead
        cos = cos_t;
    }
    double r0 = std::pow((comps.n1 - comps.n2)/(comps.n1 + comps.n2), 2);
    return r0 + (1 - r0) * pow((1-cos), 5);
}

