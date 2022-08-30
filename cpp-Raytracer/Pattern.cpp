//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "Pattern.h"

Pattern::Pattern(color a, color b):
    a(a),
    b(b)
{

}

void Pattern::SetTransform(Matrix4 new_transform) {
    m_transform = new_transform;
}

color CStripePattern::PatternAt(point p) const {
    if(int(std::floor(p.x)) % 2 == 0)
    {
        return a;
    } else
    {
        return b;
    }
}

CStripePattern::CStripePattern(color a, color b):
        Pattern(a, b)
{

}

CGradientPattern::CGradientPattern(color a, color b):
        Pattern(a, b)
{

}

color CGradientPattern::PatternAt(point p) const {
    color distance = b - a;
    double fraction = p.x - std::floor(p.x);
    return a + distance * fraction;
}

CCheckersPattern::CCheckersPattern(color a, color b) :
        Pattern(a, b)
{

}

color CCheckersPattern::PatternAt(point p) const {
    if((int(floor(p.x)) + int(floor(p.y)) + int(floor(p.z))) % 2 == 0) {
        return a;
    } else
    {
        return b;
    }
}

CTestPattern::CTestPattern(color a, color b) : Pattern(a, b) {

}

color CTestPattern::PatternAt(point p) const {
    return color(p.x, p.y, p.z);
}
