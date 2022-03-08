//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#include "CMaterial.h"

#include <memory>

bool CMaterial::operator==(const CMaterial &other) const {
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

CMaterial::CMaterial(std::shared_ptr<CPattern> pattern)
{
    this->pattern = pattern;
}

CMaterial::CMaterial()
{

}

void CMaterial::SetPattern(std::shared_ptr<CPattern> pattern) {
    this->pattern = pattern;
}




