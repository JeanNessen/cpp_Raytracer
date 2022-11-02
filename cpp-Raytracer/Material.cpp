//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#include "Material.h"


bool material::operator==(const material &other) const {
    return (
            Math::Equal(ambient, other.ambient) &&
            Math::Equal(diffuse, other.diffuse) &&
            Math::Equal(shininess, other.shininess) &&
            Math::Equal(specular, other.specular) &&
            col == other.col &&
            m_pattern == other.m_pattern &&
            Math::Equal(reflective, other.reflective)
            );
}

material::material(std::shared_ptr<pattern> pattern)
{
    this->m_pattern = pattern;
}

material::material()
{

}

void material::SetPattern(std::shared_ptr<pattern> pattern) {
    this->m_pattern = pattern;
}




