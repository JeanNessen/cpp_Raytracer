//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#include "Intersection.h"

#include <utility>

bool intersection::operator==(const intersection& pOther) const
{
    if (t != pOther.t)
    {
        return false;
    }
    if (object != pOther.object)
    {
        return false;
    }
    return true;
}

intersection::intersection(const double pT, shape_ptr  pShape):
    t(pT),
    object(std::move(pShape))
{
}

intersection* hit(std::vector<intersection> &pIntersections)
{
    intersection *hit = nullptr;
    for (auto& intersection : pIntersections)
    {
        if (intersection.t < 0)
        {
            continue;
        }
        if (hit == nullptr)
        {
            hit = &intersection;
        }
        else if (intersection.t < hit->t)
        {
            hit = &intersection;
        }
    }
    return hit;
}