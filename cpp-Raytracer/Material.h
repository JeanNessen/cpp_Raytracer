//
// Created by Jean-Luc von Nessen on 14.01.22.
//
#pragma once

#include <memory>

#include "pattern.h"
#include "Color.h"

class material {
//Methods
private:
public:
    explicit material();
    explicit material(std::shared_ptr<pattern> pattern);

    std::shared_ptr<pattern> GetPattern(){return m_pattern;}
    void SetPattern(std::shared_ptr<pattern> pattern);

    bool operator==(const material& other) const;

//Members
private:
    std::shared_ptr<pattern> m_pattern = nullptr;

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    color col{1, 1, 1};
    double reflective = 0;
    double transparency = 0;
    double refractive_index = 1;
    bool throws_shadow = true;
    color emissive{0, 0, 0};
};

