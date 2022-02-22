#include "Sphere.h"

Sphere::Sphere():
        Shape(ShapeType::sphere)
{

}


Vector Sphere::NormalAt(Point world_point) {
    //Convert point from World Space to Object Space
    Point object_point{transform.Inversed() * world_point};

    //Calculate Object Space normals
    Vector object_normal{object_point - Point(0, 0, 0)};

    //Convert Object Space normals to World Space
    Vector world_normal{transform.Inversed().Transposed() * object_normal};
    world_normal.w = 0;

    return world_normal.normalized();
}


