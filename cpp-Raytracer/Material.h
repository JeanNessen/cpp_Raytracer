//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#ifndef CPP_RAYTRACER_MATERIAL_H
#define CPP_RAYTRACER_MATERIAL_H


#include <memory>
#include "Color.h"
#include "Pattern.h"

class Material {

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    Color color{1, 1, 1};
    double reflective = 0;
    double transparency = 0;
    double refractive_index = 1;

    std::shared_ptr<Pattern> GetPattern(){return pattern;}
    void SetPattern(std::shared_ptr<Pattern> pattern);

    bool operator==(const Material& other) const;

     explicit Material(std::shared_ptr<Pattern> pattern);
     explicit Material();

private:
    std::shared_ptr<Pattern> pattern = nullptr;

};


#endif //CPP_RAYTRACER_MATERIAL_H
