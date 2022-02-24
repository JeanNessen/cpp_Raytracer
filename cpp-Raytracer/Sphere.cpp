#include "Sphere.h"
//#include "Ray.h"
//#include "Intersection.h"

Sphere::Sphere():
        Shape(ShapeType::sphere)
{

}

Vector Sphere::LocalNormalAt(Point local_point) const{
    //Calculate Object Space normals
    return Vector{local_point - Point(0, 0, 0)};
}



