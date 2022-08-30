//
// Created by Jean-Luc von Nessen on 24.02.22.
//
#pragma once

#include "color.h"
#include "Math.h"


class pattern {
//Methods
protected:
    pattern(color a, color b);

    matrix4 m_transform = Math::identiy_matrix;

public:
    [[nodiscard]] virtual color PatternAt(point p) const = 0;

    matrix4 GetTransform(){return m_transform;}
    void SetTransform(matrix4 new_transform);

//Members
private:
public:
    color a;
    color b;
};

class stripe_pattern: public pattern {

public:
    stripe_pattern(color a, color b);

    [[nodiscard]] color PatternAt(point p) const override;
};

class gradient_pattern: public pattern {

public:
    gradient_pattern(color a, color b);

    [[nodiscard]] color PatternAt(point p) const override;

};

class checkers_pattern: public pattern {

public:
    checkers_pattern(color a, color b);

    [[nodiscard]] color PatternAt(point p) const override;

};

class test_pattern: public pattern {

public:
    test_pattern(color a, color b);

    color PatternAt(point p) const override;
};

