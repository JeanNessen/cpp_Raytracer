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
    transform = new_transform;
}

Color StripePattern::PatternAt(Point p) const {
    if(int(std::floor(p.x)) % 2 == 0)
    {
        return a;
    } else
    {
        return b;
    }
}

StripePattern::StripePattern(Color a, Color b):
    Pattern(a, b)
{

}

GradientPattern::GradientPattern(Color a, Color b):
    Pattern(a, b)
{

}

Color GradientPattern::PatternAt(Point p) const {
    Color distance = b - a;
    double fraction = p.x - std::floor(p.x);
    return a + distance * fraction;
}

CheckersPattern::CheckersPattern(Color a, Color b) :
    Pattern(a, b)
{

}

Color CheckersPattern::PatternAt(Point p) const {
    if((int(floor(p.x)) + int(floor(p.y)) + int(floor(p.z))) % 2 == 0) {
        return a;
    } else
    {
        return b;
    }
}
