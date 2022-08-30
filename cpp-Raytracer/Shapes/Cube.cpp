//
// Created by Jean-Luc von Nessen on 13.03.22.
//

#include "Cube.h"
#include <algorithm>

cube::cube()
    : shape(shape_type::cube)
{

}

vector cube::local_normal_at(point pLocalPoint) const {
	const double maxc = std::max({std::abs(pLocalPoint.x), std::abs(pLocalPoint.y), std::abs(pLocalPoint.z)});

    if (maxc == std::abs(pLocalPoint.x))
    {
        return {pLocalPoint.x, 0, 0};
    }
    if (maxc == std::abs(pLocalPoint.y))
    {
        return {0, pLocalPoint.y, 0};
    }
    return {0, 0, pLocalPoint.z};
}
