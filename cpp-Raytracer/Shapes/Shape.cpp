//
// Created by Jean-Luc von Nessen on 21.02.22.
//

#include "shape.h"


int shape::m_latest_id = 0;

bool shape::operator==(const shape& pOther) const {
    if( this->m_transform == pOther.m_transform &&
        this->m_material == pOther.m_material &&
        this->id == pOther.id &&
        this->type == pOther.type)
    {
        return true;
    } else
    {
        return false;
    }
}

bool shape::operator!=(const shape &pOther) const {
    return !(*this == pOther);
}

shape::shape(const shape_type pT):
	m_transform(Math::identiy_matrix),
	m_material(Material{}),
	id(m_latest_id),
	type(pT)
{
    ++m_latest_id;
}

Vector shape::normal_at(const Point pWorldPoint) const{
	const Point localPoint{get_transform().Inversed() * pWorldPoint};
	const Vector localNormal{local_normal_at(localPoint)};
    Vector worldNormal{get_transform().Inversed().Transposed() * localNormal};
    worldNormal.w = 0;
    return worldNormal.normalized();
}

color shape::stripe_at_object(const Point pWorldPoint) const {
	const Point objectPoint{ m_transform.Inversed() * pWorldPoint};
	const Point patternPoint{get_material_const().GetPattern()->GetTransform().Inversed() * objectPoint};
    return get_material_const().GetPattern()->PatternAt(patternPoint);
}




