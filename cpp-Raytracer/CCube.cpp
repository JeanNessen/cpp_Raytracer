//
// Created by Jean-Luc von Nessen on 13.03.22.
//

#include "CCube.h"

CCube::CCube()
    : CShape(EShapeType::cube)
{

}

Vector CCube::LocalNormalAt(Point local_point) const {
    double maxc = std::max({abs(local_point.x), abs(local_point.y), abs(local_point.z)});

    if (maxc == abs(local_point.x))
    {
        return {local_point.x, 0, 0};
    }
    else if (maxc == abs(local_point.y))
    {
        return {0, local_point.y, 0};
    }
    return {0, 0, local_point.z};
}
