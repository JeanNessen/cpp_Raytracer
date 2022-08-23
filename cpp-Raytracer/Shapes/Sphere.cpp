#include "Sphere.h"
//#include "Ray.h"
//#include "Intersection.h"

Sphere::Sphere():
        shape(shape_type::sphere)
{

}

Vector Sphere::local_normal_at(const Point pLocalPoint) const{
    //Calculate Object Space normals
    return Vector{pLocalPoint - Point(0, 0, 0)};
}



