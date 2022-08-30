//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "pattern.h"

pattern::pattern(color a, color b):
    a(a),
    b(b)
{

}

void pattern::SetTransform(matrix4 new_transform) {
    m_transform = new_transform;
}

color stripe_pattern::PatternAt(point p) const {
    if(int(std::floor(p.x)) % 2 == 0)
    {
        return a;
    } else
    {
        return b;
    }
}

stripe_pattern::stripe_pattern(color a, color b):
        pattern(a, b)
{

}

CGradientPattern::CGradientPattern(color a, color b):
        pattern(a, b)
{

}

color CGradientPattern::PatternAt(point p) const {
    color distance = b - a;
    double fraction = p.x - std::floor(p.x);
    return a + distance * fraction;
}

CCheckersPattern::CCheckersPattern(color a, color b) :
        pattern(a, b)
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

CTestPattern::CTestPattern(color a, color b) : pattern(a, b) {

}

color CTestPattern::PatternAt(point p) const {
    return color(p.x, p.y, p.z);
}
