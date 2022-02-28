//
// Created by jeanl on 28/02/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/World.h"

//TEST(Multithreading, MultithreadingRenderSameAsSinglethreadRender)
//{
//    World w = DefaultWorld();
//    Camera c{11, 11, M_PI/2};
//    Point from{0, 0, -5};
//    Point to{0, 0, 0};
//    Vector up{0, 1, 0};
//    c.SetTransform(Math::ViewTransform(from, to, up));
//
//    Canvas image_multi = w.RenderMultiThread(c);
//    Canvas image_single = w.RenderSingleThread(c);
//
//    EXPECT_EQ(image_single, image_single);
//}