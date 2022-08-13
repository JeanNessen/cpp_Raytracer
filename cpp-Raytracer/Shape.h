//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#ifndef CPP_RAYTRACER_CSHAPE_H
#define CPP_RAYTRACER_CSHAPE_H

#include <memory>
#include "Math.h"
#include "Material.h"




class Shape {
public:
    enum EShapeType{
        sphere,
        plane,
        cube,
        cylinder
    };

protected:
    Matrix4 transform;

    Material material;

    static int latest_id;

    explicit Shape(EShapeType t);

    [[nodiscard]] virtual Vector LocalNormalAt(Point local_point) const = 0;

public:
    const int id;

    const EShapeType type;

    [[nodiscard]] Matrix4 GetTransform() const { return transform; }
    void SetTransform(Matrix4 t){ transform = t; }

    Material& GetMaterial() { return material; }
    [[nodiscard]] Material GetMaterialConst() const {return material;}
    void SetMaterial(Material m){ material = m; }

    bool operator==(const Shape& other) const;
    bool operator!=(const Shape& other) const;

    virtual ~Shape()= default;

    [[nodiscard]] Vector NormalAt(Point world_point) const;
    [[nodiscard]] Color StripeAtObject(Point world_point) const;

    Point saved_ray_origin;
    Vector saved_ray_direction;

};

using Shape_ptr = std::shared_ptr<Shape>;

#endif //CPP_RAYTRACER_CSHAPE_H
