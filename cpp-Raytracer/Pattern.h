//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#ifndef CPP_RAYTRACER_PATTERN_H
#define CPP_RAYTRACER_PATTERN_H

#include "Color.h"

class Pattern {
public:
    Color a;
    Color b;

    [[nodiscard]] virtual Color PatternAt(Point p) const = 0;

    Matrix4 GetTransform(){return transform;}
    void SetTransform(Matrix4 new_transform);

protected:
    Matrix4 transform = Math::identiy_matrix;

    Pattern(Color a, Color b);
};

class StripePattern: public Pattern {
public:
    StripePattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;
};

class GradientPattern: public Pattern {
public:
    GradientPattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;

};

class CheckersPattern: public Pattern {
public:
    CheckersPattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;

};

#endif //CPP_RAYTRACER_PATTERN_H
