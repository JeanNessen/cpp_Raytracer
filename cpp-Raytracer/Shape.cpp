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

Vector Shape::NormalAt(Point world_point) const{
    Point local_point{GetTransform().Inversed() * world_point};
    Vector local_normal{LocalNormalAt(local_point)};
    Vector world_normal{GetTransform().Inversed().Transposed() * local_normal};
    world_normal.w = 0;
    return world_normal.normalized();
}




