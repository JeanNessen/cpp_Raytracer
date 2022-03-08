//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#include "CShape.h"


int CShape::latest_id = 0;

bool CShape::operator==(const CShape &other) const {
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

bool CShape::operator!=(const CShape &other) const {
    return !(*this == other);
}

CShape::CShape(EShapeType t):
    id(latest_id),
    type(t),
    transform(Math::identiy_matrix),
    material(CMaterial{})
{
    ++latest_id;
}

Vector CShape::NormalAt(Point world_point) const{
    Point local_point{GetTransform().Inversed() * world_point};
    Vector local_normal{LocalNormalAt(local_point)};
    Vector world_normal{GetTransform().Inversed().Transposed() * local_normal};
    world_normal.w = 0;
    return world_normal.normalized();
}

CColor CShape::StripeAtObject(Point world_point) const {
    Point object_point{ transform.Inversed() * world_point};
    Point pattern_point{GetMaterialConst().GetPattern()->GetTransform().Inversed() * object_point};
    return GetMaterialConst().GetPattern()->PatternAt(pattern_point);
}




