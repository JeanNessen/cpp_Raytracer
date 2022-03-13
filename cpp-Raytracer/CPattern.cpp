//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "CPattern.h"

CPattern::CPattern(CColor a, CColor b):
    a(a),
    b(b)
{

}

void CPattern::SetTransform(Matrix4 new_transform) {
    m_transform = new_transform;
}

CColor CStripePattern::PatternAt(Point p) const {
    if(int(std::floor(p.x)) % 2 == 0)
    {
        return a;
    } else
    {
        return b;
    }
}

CStripePattern::CStripePattern(CColor a, CColor b):
        CPattern(a, b)
{

}

CGradientPattern::CGradientPattern(CColor a, CColor b):
        CPattern(a, b)
{

}

CColor CGradientPattern::PatternAt(Point p) const {
    CColor distance = b - a;
    double fraction = p.x - std::floor(p.x);
    return a + distance * fraction;
}

CCheckersPattern::CCheckersPattern(CColor a, CColor b) :
        CPattern(a, b)
{

}

CColor CCheckersPattern::PatternAt(Point p) const {
    if((int(floor(p.x)) + int(floor(p.y)) + int(floor(p.z))) % 2 == 0) {
        return a;
    } else
    {
        return b;
    }
}

CTestPattern::CTestPattern(CColor a, CColor b) : CPattern(a, b) {

}

CColor CTestPattern::PatternAt(Point p) const {
    return CColor(p.x, p.y, p.z);
}
