//
// Created by Jean-Luc von Nessen on 13.03.22.
//

#include "Cube.h"
#include <algorithm>

Cube::Cube()
    : Shape(EShapeType::cube)
{

}

Vector Cube::LocalNormalAt(Point local_point) const {
    double maxc = std::max({std::abs(local_point.x), std::abs(local_point.y), std::abs(local_point.z)});

    if (maxc == std::abs(local_point.x))
    {
        return {local_point.x, 0, 0};
    }
    else if (maxc == std::abs(local_point.y))
    {
        return {0, local_point.y, 0};
    }
    return {0, 0, local_point.z};
}
