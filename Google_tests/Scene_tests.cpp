//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include <algorithm>

#include "gtest/gtest.h"

#include "../cpp-Raytracer/World.h"
#include "../cpp-Raytracer/World.cpp"

TEST(World, WorldCreation)
{
    World w{};

    EXPECT_TRUE(w.GetWorldLights().empty());
    EXPECT_TRUE(w.GetWorldObjects().empty());
}

TEST(World, DefaultWorld)
{
    PointLight light{Color(1, 1, 1), Point(-10, 10, -10)};

    Sphere sphere_1{1};
    sphere_1.GetMaterial().color = Color{0.8, 1.0, 0.6};
    sphere_1.GetMaterial().diffuse = 0.7;
    sphere_1.GetMaterial().specular = 0.2;

    Sphere sphere_2{2};
    sphere_2.SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    World w = DefaultWorld();

    //Check if the default world contains the correct light
    auto default_light_it = std::find(w.GetWorldLights().begin(), w.GetWorldLights().end(), light);
    EXPECT_NE(default_light_it, w.GetWorldLights().end());

    //Check if the default world contains the correct spheres
    auto default_sphere_1_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_1);
    EXPECT_NE(default_sphere_1_it, w.GetWorldObjects().end());

    auto default_sphere_2_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_2);
    EXPECT_NE(default_sphere_2_it, w.GetWorldObjects().end());
}

TEST(World, IntersectWorldWithRay)
{
    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

    std::vector<Intersection> xs = w.IntersectWorld(r);

    EXPECT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}