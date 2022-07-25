//
// Created by Jean-Luc von Nessen on 24.02.22.
//
#pragma once

#include "Color.h"
#include "Math.h"


class Pattern {
//Methods
protected:
    Pattern(Color a, Color b);

    Matrix4 m_transform = Math::identiy_matrix;

public:
    [[nodiscard]] virtual Color PatternAt(Point p) const = 0;

    Matrix4 GetTransform(){return m_transform;}
    void SetTransform(Matrix4 new_transform);

//Members
private:
public:
    Color a;
    Color b;
};

class CStripePattern: public Pattern {

public:
    CStripePattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;
};

class CGradientPattern: public Pattern {

public:
    CGradientPattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;

};

class CCheckersPattern: public Pattern {

public:
    CCheckersPattern(Color a, Color b);

    [[nodiscard]] Color PatternAt(Point p) const override;

};

class CTestPattern: public Pattern {

public:
    CTestPattern(Color a, Color b);

    Color PatternAt(Point p) const override;
};

