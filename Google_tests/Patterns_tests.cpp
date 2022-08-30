//
// Created by Jean-Luc von Nessen on 24.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/pattern.h"
//#include "../cpp-Raytracer/Pattern.cpp"

#include "../cpp-Raytracer/Shapes/Sphere.h"

TEST(Patterns, CreatingAStripePattern)
{
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));

    EXPECT_EQ(pattern->a, colors::white);
    EXPECT_EQ(pattern->b, colors::black);
}

TEST(Patterns, AStripePatternsIsConstantInY)
{
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));

    EXPECT_EQ(pattern->PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(0, 1, 0)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(0, 2, 0)), colors::white);
}

TEST(Patterns, AStripePatternsIsConstantInZ)
{
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));


    EXPECT_EQ(pattern->PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(0, 0, 1)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(0, 0, 2)), colors::white);
}

TEST(Patterns, AStripePatternAlternatesInX)
{
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));


    EXPECT_EQ(pattern->PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(0.9, 0, 0)), colors::white);
    EXPECT_EQ(pattern->PatternAt(point(1, 0, 0)), colors::black);
    EXPECT_EQ(pattern->PatternAt(point(-0.1, 0, 0)), colors::black);
    EXPECT_EQ(pattern->PatternAt(point(-1, 0, 0)), colors::black);
    EXPECT_EQ(pattern->PatternAt(point(-1.1, 0, 0)), colors::white);
}

TEST(Patterns, StripesWithObjectTransformation)
{
    Sphere object{};
    object.set_transform(Math::Scaling(2, 2, 2));
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));
    object.get_material().SetPattern(pattern);

    color c = object.stripe_at_object(point(1.5, 0, 0));

    EXPECT_EQ(c, colors::white);
}

TEST(Patterns, StripesWithPatternTransformation)
{
    Sphere object{};
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));
    pattern->SetTransform(Math::Scaling(2, 2, 2));
    object.get_material().SetPattern(pattern);


    color c = object.stripe_at_object(point(1.5, 0, 0));

    EXPECT_EQ(c, colors::white);
}

TEST(Patterns, StripesWithBothObjectAndPatternTransformation)
{
    Sphere object{};
    object.set_transform(Math::Scaling(2, 2, 2));
    std::shared_ptr<pattern> pattern (new stripe_pattern(colors::white, colors::black));
    pattern->SetTransform(Math::Translation(0.5, 0, 0));
    object.get_material().SetPattern(pattern);

    color c = object.stripe_at_object(point(2.5, 0, 0));

    EXPECT_EQ(c, colors::white);

}

TEST(Patterns, GradientLinearlyInterpolatesBetweenColors)
{
    gradient_pattern pattern{colors::white, colors::black};

    EXPECT_EQ(pattern.PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0.25, 0, 0)), color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.PatternAt(point(0.5, 0, 0)), color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.PatternAt(point(0.75, 0, 0)), color(0.25, 0.25, 0.25));
}

TEST(Patterns, CheckersShouldRepeatInX)
{
    checkers_pattern pattern{colors::white, colors::black};

    EXPECT_EQ(pattern.PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0.99, 0, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(1.01, 0, 0)), colors::black);
}

TEST(Patterns, CheckersShouldRepeatInY)
{
    checkers_pattern pattern{colors::white, colors::black};

    EXPECT_EQ(pattern.PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0, 0.99, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0, 1.01, 0)), colors::black);
}

TEST(Patterns, CheckersShouldRepeatInZ)
{
    checkers_pattern pattern{colors::white, colors::black};

    EXPECT_EQ(pattern.PatternAt(point(0, 0, 0)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0, 0, 0.99)), colors::white);
    EXPECT_EQ(pattern.PatternAt(point(0, 0, 1.01)), colors::black);
}