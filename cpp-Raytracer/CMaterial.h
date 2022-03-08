//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#ifndef CPP_RAYTRACER_CMATERIAL_H
#define CPP_RAYTRACER_CMATERIAL_H


#include <memory>
#include "CColor.h"
#include "CPattern.h"

class CMaterial {

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    CColor color{1, 1, 1};
    double reflective = 0;
    double transparency = 0;
    double refractive_index = 1;

    std::shared_ptr<CPattern> GetPattern(){return pattern;}
    void SetPattern(std::shared_ptr<CPattern> pattern);

    bool operator==(const CMaterial& other) const;

    explicit CMaterial(std::shared_ptr<CPattern> pattern);
    explicit CMaterial();

private:
    std::shared_ptr<CPattern> pattern = nullptr;

};


#endif //CPP_RAYTRACER_CMATERIAL_H
