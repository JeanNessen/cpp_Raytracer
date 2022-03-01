//
// Created by Jean-Luc von Nessen on 01.03.22.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/Material.h"

TEST(Refractions, TransparencyAndRefractiveIndexOfDefaultMaterial)
{
    Material m{};

    EXPECT_EQ(m.transparency, 0);
    EXPECT_EQ(m.refractive_index, 1);
}