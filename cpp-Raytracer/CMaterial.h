//
// Created by Jean-Luc von Nessen on 14.01.22.
//
#pragma once

#include <memory>

#include "CPattern.h"

class CMaterial {
//Methods
private:
public:
    explicit CMaterial();
    explicit CMaterial(std::shared_ptr<CPattern> pattern);

    std::shared_ptr<CPattern> GetPattern(){return m_pattern;}
    void SetPattern(std::shared_ptr<CPattern> pattern);

    bool operator==(const CMaterial& other) const;

//Members
private:
    std::shared_ptr<CPattern> m_pattern = nullptr;

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    CColor color{1, 1, 1};
    double reflective = 0;
    double transparency = 0;
    double refractive_index = 1;
    bool throws_shadow = true;
};

