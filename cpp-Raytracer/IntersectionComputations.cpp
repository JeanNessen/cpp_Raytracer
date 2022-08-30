//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "IntersectionComputations.h"

#include <utility>


intersection_computations::intersection_computations(const double pT, shape_ptr  pObject, const point pPoint, const Vector pEyeV, const Vector pNormalV, const double pN1, const double pN2):
        t(pT),
        object(std::move(pObject)),
		intersect_point(pPoint),
        eye_v(pEyeV),
        normal_v(pNormalV),
        n1(pN1),
        n2(pN2)
{
    if(Math::Dot(pNormalV, pEyeV) < 0)
    {
        //The hit occurred inside the object, invert the normal
        inside = true;
        this->normal_v.x = -pNormalV.x;
        this->normal_v.y = -pNormalV.y;
        this->normal_v.z = -pNormalV.z;
    }
    else
    {
        inside = false;
    }
    over_point = point{this->intersect_point + this->normal_v * EPSILON};
    under_point = point{this->intersect_point - this->normal_v * EPSILON};

}



intersection_computations PrepareComputations(const intersection& pIntersection, const ray pRay, std::vector<intersection> xs) {
    if(xs.empty())
    {
        xs.push_back(pIntersection);
    }

    //Copy intersection properties for convenience
    const double compsT {pIntersection.t};
    const shape_ptr compsObject {pIntersection.object};

    //precompute needed values
    const point compsPoint{pRay.position(pIntersection.t)};
    const Vector compsEyeV{-pRay.direction.x, -pRay.direction.y, -pRay.direction.z};
    const Vector compsNormalV{pIntersection.object->normal_at(pRay.position(pIntersection.t))};

    const std::vector<double> n1n2 = find_refractive_indices(pIntersection, xs);



    intersection_computations comps{
            compsT,
            compsObject,
            compsPoint,
            compsEyeV,
            compsNormalV,
            n1n2[0],
            n1n2[1]
    };

    comps.reflect_v = pRay.direction.Reflect(compsNormalV);

    return comps;
}
std::vector<double> find_refractive_indices(const intersection& pIntersection, const std::vector<intersection>& xs) {

    double local_n1, local_n2;

    std::vector<shape_ptr> containers;

    //Find the refractive indices for the materials of this intersection
    for (const intersection& i: xs) {

        //If i is the hit, n1 is the refractive index of the last object in containers, or 1 if containers is empty
        if (i == pIntersection)
        {
            if(containers.empty())
            {
                local_n1 = 1;
            }
            else
            {
                local_n1 = containers[containers.size()-1]->get_material().refractive_index;
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

        if(i == pIntersection)
        {
            if(containers.empty())
            {
                local_n2 = 1;
            }
            else
            {
                local_n2 = containers[containers.size()-1]->get_material().refractive_index;
            }
            break;
        }
    }

    return std::vector<double>{local_n1, local_n2};
}

double Schlick(const intersection_computations& comps) {
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

