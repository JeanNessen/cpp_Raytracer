//
// Created by Jean-Luc von Nessen on 07.03.22.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/Math.h"

TEST(RandomNumbers, RandomDoubleGivesDifferentNumberEveryTime){
    double n1 = Math::GetRandomDouble(0, 1);
    double n2 = Math::GetRandomDouble(0, 1);

    EXPECT_TRUE(n1 <= 1);
    EXPECT_TRUE(n2 <= 1);
    EXPECT_TRUE(n1 >= 0);
    EXPECT_TRUE(n2 >= 0);
    EXPECT_NE(n1, n2);
}

