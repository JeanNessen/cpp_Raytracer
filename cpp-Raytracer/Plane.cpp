//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "Plane.h"


Plane::Plane():
        Shape(EShapeType::plane)
{

}

Vector Plane::LocalNormalAt(Point local_point) const{
    return Vector(0, 1, 0);
}


