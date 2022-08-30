//
// Created by Jean-Luc von Nessen on 22.02.22.
//
#pragma once

#include "shape.h"


class plane final : public shape {
//Methods
public:
    plane();

	[[nodiscard]] Vector local_normal_at(point pLocalPoint) const override;
};

using plane_ptr = std::shared_ptr<plane>;

