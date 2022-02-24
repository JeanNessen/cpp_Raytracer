//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#include "Intersection.h"

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

Intersection::Intersection(double t, const std::shared_ptr<Shape> shape):
    t(t),
    object(shape)
{
}




std::vector<Intersection> Intersections(std::initializer_list<Intersection> args)
{
    std::vector<Intersection> intersections;

    for (auto i : args)
    {
        intersections.push_back(i);
    }

    return intersections;
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