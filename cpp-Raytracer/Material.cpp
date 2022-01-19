//
// Created by Jean-Luc von Nessen on 14.01.22.
//

#include "Material.h"

bool Material::operator==(const Material &other) const {
    return (
            Math::Equal(ambient, other.ambient) &&
            Math::Equal(diffuse, other.diffuse) &&
            Math::Equal(shininess, other.shininess) &&
            Math::Equal(specular, other.specular) &&
            color == other.color
            );
}
