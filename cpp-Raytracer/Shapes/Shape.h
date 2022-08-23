//
// Created by Jean-Luc von Nessen on 21.02.22.
//
#pragma once

#include <memory>
#include <utility>
#include "../Math.h"
#include "../Material.h"




class shape {
public:
    enum class shape_type{
        sphere,
        plane,
        cube,
        cylinder,
        cone
    };

protected:
    Matrix4 m_transform;

    Material m_material;

    static int m_latest_id;

    explicit shape(shape_type pT);

    [[nodiscard]] virtual Vector local_normal_at(Point local_point) const = 0;

public:
    const int id;

    const shape_type type;

    [[nodiscard]] Matrix4 get_transform() const { return m_transform; }
    void set_transform(const Matrix4 pT){ m_transform = pT; }

    Material& get_material() { return m_material; }
    [[nodiscard]] Material get_material_const() const {return m_material;}
    void set_material(Material pM){ m_material = std::move(pM); }

    bool operator==(const shape& pOther) const;
    bool operator!=(const shape& pOther) const;

    virtual ~shape()= default;

    [[nodiscard]] Vector normal_at(Point pWorldPoint) const;
    [[nodiscard]] color stripe_at_object(Point pWorldPoint) const;

    Point saved_ray_origin;
    Vector saved_ray_direction;

};

using shape_ptr = std::shared_ptr<shape>;

