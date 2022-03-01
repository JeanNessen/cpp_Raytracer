//
// Created by Jean-Luc von Nessen on 26.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Camera.h"
//#include "../cpp-Raytracer/Camera.cpp"

TEST(Camera, RandomCanvasPointIsRandom)
{
    Camera c{10, 10, M_PI/2};

    Point p1 = c.GetRandomPointOnAperture();
    Point p2 = c.GetRandomPointOnAperture();

    EXPECT_NE(p1, p2);
}
