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
            m_pattern == other.m_pattern &&
            Math::Equal(reflective, other.reflective)
            );
}

Material::Material(std::shared_ptr<Pattern> pattern)
{
    this->m_pattern = pattern;
}

Material::Material()
{

}

void Material::SetPattern(std::shared_ptr<Pattern> pattern) {
    this->m_pattern = pattern;
}




