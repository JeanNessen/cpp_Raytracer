//
// Created by Jean-Luc von Nessen on 13.03.22.
//
#pragma once

#include "shape.h"


class cube final : public shape {
//Methods
private:
public:
    cube();

[[nodiscard]] vector local_normal_at(point pLocalPoint) const override;

};

using cube_ptr = std::shared_ptr<cube>;
