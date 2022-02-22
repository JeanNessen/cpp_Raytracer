//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#ifndef CPP_RAYTRACER_SHAPE_H
#define CPP_RAYTRACER_SHAPE_H

#include "Math.h"
#include "Material.h"

enum ShapeType{
    sphere,
    plane
};

class Shape {

protected:
    Matrix4 transform;

    Material material;

    static int latest_id;

    explicit Shape(ShapeType t);

public:
    const int id;

    const ShapeType type;

    Matrix4 GetTransform(){ return transform; }
    void SetTransform(Matrix4 t){ transform = t; }

    Material& GetMaterial(){ return material; }
    void SetMaterial(Material m){ material = m; }

    bool operator==(const Shape& other) const;
    bool operator!=(const Shape& other) const;

    virtual ~Shape()= default;

    virtual Vector NormalAt(Point point);

    Point saved_ray_origin;
    Vector saved_ray_direction;

};

#endif //CPP_RAYTRACER_SHAPE_H
