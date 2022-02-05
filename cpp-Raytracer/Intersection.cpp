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