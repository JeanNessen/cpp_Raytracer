//
// Created by Jean-Luc von Nessen on 22.02.22.
//

#ifndef CPP_RAYTRACER_PLANE_H
#define CPP_RAYTRACER_PLANE_H

#include "Shape.h"


class Plane: public Shape {

public:
    Plane();

    Vector LocalNormalAt(Point local_point) const override;
};

using Plane_ptr = std::shared_ptr<Plane>;


#endif //CPP_RAYTRACER_PLANE_H
