//
// Created by Jean-Luc von Nessen on 24.02.22.
//
#pragma once

#include "color.h"
#include "Math.h"


class Pattern {
//Methods
protected:
    Pattern(color a, color b);

    Matrix4 m_transform = Math::identiy_matrix;

public:
    [[nodiscard]] virtual color PatternAt(Point p) const = 0;

    Matrix4 GetTransform(){return m_transform;}
    void SetTransform(Matrix4 new_transform);

//Members
private:
public:
    color a;
    color b;
};

class CStripePattern: public Pattern {

public:
    CStripePattern(color a, color b);

    [[nodiscard]] color PatternAt(Point p) const override;
};

class CGradientPattern: public Pattern {

public:
    CGradientPattern(color a, color b);

    [[nodiscard]] color PatternAt(Point p) const override;

};

class CCheckersPattern: public Pattern {

public:
    CCheckersPattern(color a, color b);

    [[nodiscard]] color PatternAt(Point p) const override;

};

class CTestPattern: public Pattern {

public:
    CTestPattern(color a, color b);

    color PatternAt(Point p) const override;
};

