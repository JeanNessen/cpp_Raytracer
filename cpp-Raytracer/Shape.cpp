//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#include "Shape.h"
//#include "Ray.h"

int Shape::latest_id = 0;

bool Shape::operator==(const Shape &other) const {
    if( this->transform == other.transform &&
        this->material == other.material &&
        this->id == other.id &&
        this->type == other.type)
    {
        return true;
    } else
    {
        return false;
    }
}

bool Shape::operator!=(const Shape &other) const {
    return !(*this == other);
}

Shape::Shape(ShapeType t):
    id(latest_id),
    type(t),
    transform(Math::identiy_matrix),
    material(Material{})
{
    ++latest_id;
}


