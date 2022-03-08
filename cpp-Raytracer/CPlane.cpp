//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "CPlane.h"


CPlane::CPlane():
        CShape(EShapeType::plane)
{

}

Vector CPlane::LocalNormalAt(Point local_point) const{
    return Vector(0, 1, 0);
}


