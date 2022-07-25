//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#include "Intersection.h"

#include <utility>

bool Intersection::operator==(const Intersection& other) const
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

Intersection::Intersection(double t, Shape_ptr  shape):
    t(t),
    object(std::move(shape))
{
}

Intersection* Hit(std::vector<Intersection> &intersections)
{
    Intersection *hit = nullptr;
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