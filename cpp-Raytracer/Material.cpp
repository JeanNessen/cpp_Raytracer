//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#include "Material.h"

#include <memory>

bool Material::operator==(const Material &other) const {
    return (
            Math::Equal(ambient, other.ambient) &&
            Math::Equal(diffuse, other.diffuse) &&
            Math::Equal(shininess, other.shininess) &&
            Math::Equal(specular, other.specular) &&
            color == other.color &&
            pattern == other.pattern &&
            Math::Equal(reflective, other.reflective)
            );
}

Material::Material(std::shared_ptr<Pattern> pattern, double ambient, double diffuse, double specular, double shininess, Color color, double reflective):
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    shininess(shininess),
    color(color),
    reflective(reflective)
{
    this->pattern = pattern;
}

Material::Material(double ambient, double diffuse, double specular, double shininess, Color color, double reflective):
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        shininess(shininess),
        color(color),
        reflective(reflective)
{

}

void Material::SetPattern(std::shared_ptr<Pattern> pattern) {
    this->pattern = pattern;
}




