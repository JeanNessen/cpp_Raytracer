//
// Created by Jean-Luc von Nessen on 14.01.22.
//
#pragma once

#include <memory>

#include "Pattern.h"

class Material {
//Methods
private:
public:
    explicit Material();
    explicit Material(std::shared_ptr<Pattern> pattern);

    std::shared_ptr<Pattern> GetPattern(){return m_pattern;}
    void SetPattern(std::shared_ptr<Pattern> pattern);

    bool operator==(const Material& other) const;

//Members
private:
    std::shared_ptr<Pattern> m_pattern = nullptr;

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    color color{1, 1, 1};
    double reflective = 0;
    double transparency = 0;
    double refractive_index = 1;
    bool throws_shadow = true;
};

