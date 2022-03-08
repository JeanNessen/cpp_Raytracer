//
// Created by Jean-Luc von Nessen on 24.02.22.
//
#pragma once

#include "CColor.h"

class CPattern {
public:
    CColor a;
    CColor b;

    [[nodiscard]] virtual CColor PatternAt(Point p) const = 0;

    Matrix4 GetTransform(){return transform;}
    void SetTransform(Matrix4 new_transform);

protected:
    Matrix4 transform = Math::identiy_matrix;

    CPattern(CColor a, CColor b);
};

class CStripePattern: public CPattern {
public:
    CStripePattern(CColor a, CColor b);

    [[nodiscard]] CColor PatternAt(Point p) const override;
};

class CGradientPattern: public CPattern {
public:
    CGradientPattern(CColor a, CColor b);

    [[nodiscard]] CColor PatternAt(Point p) const override;

};

class CCheckersPattern: public CPattern {
public:
    CCheckersPattern(CColor a, CColor b);

    [[nodiscard]] CColor PatternAt(Point p) const override;

};

class CTestPattern: public CPattern {
    public:
    CTestPattern(CColor a, CColor b);

    CColor PatternAt(Point p) const override;
};

