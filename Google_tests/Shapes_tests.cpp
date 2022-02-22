//
// Created by Jean-Luc von Nessen on 21.02.22.
//



#include "gtest/gtest.h"

#include "../cpp-Raytracer/Shape.h"
#include "../cpp-Raytracer/Shape.cpp"

#include "../cpp-Raytracer/Sphere.h"
//#include "../cpp-Raytracer/Sphere.cpp"

#include "../cpp-Raytracer/Plane.h"
#include "../cpp-Raytracer/Plane.cpp"

#include "../cpp-Raytracer/Ray.h"

#include <vector>

TEST(Spheres, TheDefaultTransformation)
{
    Sphere s{};

    EXPECT_EQ(s.GetTransform(), Math::identiy_matrix);
}

TEST(Spheres, AssigningATransformation)
{
    Sphere s{};

    s.SetTransform(Math::Translation(2, 3, 4));

    EXPECT_EQ(s.GetTransform(), Math::Translation(2, 3, 4));
}

TEST(Spheres, TheDefaultMaterial)
{
    Sphere s{};

    EXPECT_EQ(s.GetMaterial(), Material{});
}

TEST(Spheres, AssigningAMaterial)
{
    Sphere s{};
    Material m{};
    m.ambient = 1;

    s.SetMaterial(m);

    EXPECT_EQ(s.GetMaterial(), m);
}

TEST(Spheres, IntersectingAScaledSphereWithARay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere s{};

    s.SetTransform(Math::Scaling(2, 2, 2));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(s.saved_ray_origin, Point(0, 0, -2.5));
    EXPECT_EQ(s.saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Planes, TheDefaultTransformation)
{
    Plane p{};

    EXPECT_EQ(p.GetTransform(), Math::identiy_matrix);
}

TEST(Planes, AssigningATransformation)
{
    Plane p{};

    p.SetTransform(Math::Translation(2, 3, 4));

    EXPECT_EQ(p.GetTransform(), Math::Translation(2, 3, 4));
}

TEST(Planes, TheDefaultMaterial)
{
    Plane p{};

    EXPECT_EQ(p.GetMaterial(), Material{});
}

TEST(Planes, AssigningAMaterial)
{
    Plane p{};
    Material m{};
    m.ambient = 1;

    p.SetMaterial(m);

    EXPECT_EQ(p.GetMaterial(), m);
}