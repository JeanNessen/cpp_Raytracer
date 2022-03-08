//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#include "SIntersection.h"

#include <utility>

bool SIntersection::operator==(const SIntersection& other) const
{
    if (t != other.t)
    {
        return false;
    }
    if (object != other.object)
    {
        return false;
    }
    return true;
}

SIntersection::SIntersection(double t, Shape_ptr  shape):
    t(t),
    object(std::move(shape))
{
}

SIntersection* Hit(std::vector<SIntersection> &intersections)
{
    SIntersection *hit = nullptr;
    for (int i = 0; i < intersections.size(); i++)
    {
        if (intersections[i].t < 0)
        {
            continue;
        }
        if (hit == nullptr)
        {
            hit = &intersections[i];
        }
        else if (intersections[i].t < hit->t)
        {
            hit = &intersections[i];
        }
    }
    return hit;
}