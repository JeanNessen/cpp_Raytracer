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
    matrix4 m_transform;

    material m_material;

    static int m_latest_id;

    explicit shape(shape_type pT);

    [[nodiscard]] virtual vector local_normal_at(point local_point) const = 0;

public:
    const int id;

    const shape_type type;

    [[nodiscard]] matrix4 get_transform() const { return m_transform; }
    void set_transform(const matrix4 pT){ m_transform = pT; }

    material& get_material() { return m_material; }
    [[nodiscard]] material get_material_const() const {return m_material;}
    void set_material(material pM){ m_material = std::move(pM); }

    bool operator==(const shape& pOther) const;
    bool operator!=(const shape& pOther) const;

    virtual ~shape()= default;

    [[nodiscard]] vector normal_at(point pWorldPoint) const;
    [[nodiscard]] color stripe_at_object(point pWorldPoint) const;

    point saved_ray_origin;
    vector saved_ray_direction;

};

using shape_ptr = std::shared_ptr<shape>;

