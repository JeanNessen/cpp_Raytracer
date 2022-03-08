#include "CSphere.h"
//#include "CRay.h"
//#include "SIntersection.h"

CSphere::CSphere():
        CShape(EShapeType::sphere)
{

}

Vector CSphere::LocalNormalAt(Point local_point) const{
    //Calculate Object Space normals
    return Vector{local_point - Point(0, 0, 0)};
}



