//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Pattern.h"
//#include "../cpp-Raytracer/Pattern.cpp"

#include "../cpp-Raytracer/Sphere.h"

TEST(Patterns, CreatingAStripePattern)
{
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));

    EXPECT_EQ(pattern->a, color::white);
    EXPECT_EQ(pattern->b, color::black);
}

TEST(Patterns, AStripePatternsIsConstantInY)
{
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));

    EXPECT_EQ(pattern->PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(0, 1, 0)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(0, 2, 0)), color::white);
}

TEST(Patterns, AStripePatternsIsConstantInZ)
{
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));


    EXPECT_EQ(pattern->PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(0, 0, 1)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(0, 0, 2)), color::white);
}

TEST(Patterns, AStripePatternAlternatesInX)
{
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));


    EXPECT_EQ(pattern->PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(0.9, 0, 0)), color::white);
    EXPECT_EQ(pattern->PatternAt(Point(1, 0, 0)), color::black);
    EXPECT_EQ(pattern->PatternAt(Point(-0.1, 0, 0)), color::black);
    EXPECT_EQ(pattern->PatternAt(Point(-1, 0, 0)), color::black);
    EXPECT_EQ(pattern->PatternAt(Point(-1.1, 0, 0)), color::white);
}

TEST(Patterns, StripesWithObjectTransformation)
{
    Sphere object{};
    object.SetTransform(Math::Scaling(2, 2, 2));
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));
    object.GetMaterial().SetPattern(pattern);

    Color c = object.StripeAtObject(Point(1.5, 0, 0));

    EXPECT_EQ(c, color::white);
}

TEST(Patterns, StripesWithPatternTransformation)
{
    Sphere object{};
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));
    pattern->SetTransform(Math::Scaling(2, 2, 2));
    object.GetMaterial().SetPattern(pattern);


    Color c = object.StripeAtObject(Point(1.5, 0, 0));

    EXPECT_EQ(c, color::white);
}

TEST(Patterns, StripesWithBothObjectAndPatternTransformation)
{
    Sphere object{};
    object.SetTransform(Math::Scaling(2, 2, 2));
    std::shared_ptr<Pattern> pattern (new CStripePattern(color::white, color::black));
    pattern->SetTransform(Math::Translation(0.5, 0, 0));
    object.GetMaterial().SetPattern(pattern);

    Color c = object.StripeAtObject(Point(2.5, 0, 0));

    EXPECT_EQ(c, color::white);

}

TEST(Patterns, GradientLinearlyInterpolatesBetweenColors)
{
    CGradientPattern pattern{color::white, color::black};

    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.PatternAt(Point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.PatternAt(Point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

TEST(Patterns, CheckersShouldRepeatInX)
{
    CCheckersPattern pattern{color::white, color::black};

    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0.99, 0, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(1.01, 0, 0)), color::black);
}

TEST(Patterns, CheckersShouldRepeatInY)
{
    CCheckersPattern pattern{color::white, color::black};

    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0, 0.99, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0, 1.01, 0)), color::black);
}

TEST(Patterns, CheckersShouldRepeatInZ)
{
    CCheckersPattern pattern{color::white, color::black};

    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 0)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 0.99)), color::white);
    EXPECT_EQ(pattern.PatternAt(Point(0, 0, 1.01)), color::black);
}