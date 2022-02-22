//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "Plane.h"
//#include "Ray.h"

Plane::Plane():
    Shape(ShapeType::plane)
{

}

Vector Plane::NormalAt(Point point) {
    return Vector();
}

