//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "Pattern.h"

Pattern::Pattern(Color a, Color b):
    a(a),
    b(b)
{

}

void Pattern::SetTransform(Matrix4 new_transform) {
    m_transform = new_transform;
}

Color CStripePattern::PatternAt(Point p) const {
    if(int(std::floor(p.x)) % 2 == 0)
    {
        return a;
    } else
    {
        return b;
    }
}

CStripePattern::CStripePattern(Color a, Color b):
        Pattern(a, b)
{

}

CGradientPattern::CGradientPattern(Color a, Color b):
        Pattern(a, b)
{

}

Color CGradientPattern::PatternAt(Point p) const {
    Color distance = b - a;
    double fraction = p.x - std::floor(p.x);
    return a + distance * fraction;
}

CCheckersPattern::CCheckersPattern(Color a, Color b) :
        Pattern(a, b)
{

}

Color CCheckersPattern::PatternAt(Point p) const {
    if((int(floor(p.x)) + int(floor(p.y)) + int(floor(p.z))) % 2 == 0) {
        return a;
    } else
    {
        return b;
    }
}

CTestPattern::CTestPattern(Color a, Color b) : Pattern(a, b) {

}

Color CTestPattern::PatternAt(Point p) const {
    return Color(p.x, p.y, p.z);
}
