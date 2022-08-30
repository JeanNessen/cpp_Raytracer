#include "Sphere.h"
//#include "Ray.h"
//#include "Intersection.h"

Sphere::Sphere():
        shape(shape_type::sphere)
{

}

vector Sphere::local_normal_at(const point pLocalPoint) const{
    //Calculate Object Space normals
    return vector{pLocalPoint - point(0, 0, 0)};
}



