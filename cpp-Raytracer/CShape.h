//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#ifndef CPP_RAYTRACER_CSHAPE_H
#define CPP_RAYTRACER_CSHAPE_H

#include <memory>
#include "Math.h"
#include "CMaterial.h"


enum EShapeType{
    sphere,
    plane
};

class CShape {

protected:
    Matrix4 transform;

    CMaterial material;

    static int latest_id;

    explicit CShape(EShapeType t);

    [[nodiscard]] virtual Vector LocalNormalAt(Point local_point) const = 0;

public:
    const int id;

    const EShapeType type;

    [[nodiscard]] Matrix4 GetTransform() const { return transform; }
    void SetTransform(Matrix4 t){ transform = t; }

    CMaterial& GetMaterial() { return material; }
    [[nodiscard]] CMaterial GetMaterialConst() const {return material;}
    void SetMaterial(CMaterial m){ material = m; }

    bool operator==(const CShape& other) const;
    bool operator!=(const CShape& other) const;

    virtual ~CShape()= default;

    [[nodiscard]] Vector NormalAt(Point world_point) const;
    [[nodiscard]] CColor StripeAtObject(Point world_point) const;

    Point saved_ray_origin;
    Vector saved_ray_direction;

};

using Shape_ptr = std::shared_ptr<CShape>;

#endif //CPP_RAYTRACER_CSHAPE_H
