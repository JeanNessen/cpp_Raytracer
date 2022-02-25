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

    virtual Vector LocalNormalAt(Point local_point) const = 0;

public:
    const int id;

    const ShapeType type;

    Matrix4 GetTransform() const { return transform; }
    void SetTransform(Matrix4 t){ transform = t; }

    Material& GetMaterial() { return material; }
    Material GetMaterialConst() const {return material;}
    void SetMaterial(Material m){ material = m; }

    bool operator==(const Shape& other) const;
    bool operator!=(const Shape& other) const;

    virtual ~Shape()= default;

    Vector NormalAt(Point world_point) const;
    Color StripeAtObject(Point world_point) const;

    Point saved_ray_origin;
    Vector saved_ray_direction;

};

#endif //CPP_RAYTRACER_SHAPE_H
