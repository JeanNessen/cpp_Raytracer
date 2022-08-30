//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#include "Plane.h"


plane::plane():
        shape(shape_type::plane)
{

}

vector plane::local_normal_at(point pLocalPoint) const{
    return {0, 1, 0};
}


