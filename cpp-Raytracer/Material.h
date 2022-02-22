//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#ifndef CPP_RAYTRACER_MATERIAL_H
#define CPP_RAYTRACER_MATERIAL_H


#include "Color.h"

class Material {

public:
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0;
    Color color{1, 1, 1};

    bool operator==(const Material& other) const;
};


#endif //CPP_RAYTRACER_MATERIAL_H
