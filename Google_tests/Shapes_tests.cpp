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
    std::shared_ptr<Sphere> s (new Sphere());

    s->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(s->saved_ray_origin, Point(0, 0, -2.5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Spheres, IntersectingATranslatedSphereWithARay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Sphere> s(new Sphere());

    s->SetTransform(Math::Translation(5, 0, 0));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(s->saved_ray_origin, Point(-5, 0, -5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 1));
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

TEST(Planes, IntersectingAScaledPlaneWithARay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Plane> p (new Plane());

    p->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<Intersection> xs = r.Intersect(p);

    EXPECT_EQ(p->saved_ray_origin, Point(0, 0, -2.5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Planes, IntersectingATranslatedPlaneWithARay)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Plane> p (new Plane());

    p->SetTransform(Math::Translation(5, 0, 0));
    std::vector<Intersection> xs = r.Intersect(p);

    EXPECT_EQ(p->saved_ray_origin, Point(-5, 0, -5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 1));
}

TEST(Planes, TheNormalOfAPlaneIsConstantEverywhere)
{
    Plane p{};

    Vector n1 = p.LocalNormalAt(Point(0, 0, 0));
    Vector n2 = p.LocalNormalAt(Point(10, 0, -10));
    Vector n3 = p.LocalNormalAt(Point(-5, 0, 150));

    Vector n = Vector(0, 1, 0);

    EXPECT_EQ(n1, n);
    EXPECT_EQ(n2, n);
    EXPECT_EQ(n3, n);
}

TEST(Planes, IntersectWithARayParallelToThePlane)
{
    std::shared_ptr<Plane> p (new Plane());
    Ray r{Point(0, 10, 10), Vector(0, 0, 1)};

    std::vector<Intersection> xs = r.LocalIntersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, IntersectWithACoplanarRay)
{
    std::shared_ptr<Plane> p (new Plane());
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};

    std::vector<Intersection> xs = r.LocalIntersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, ARayIntersectingAPlaneFormAbove)
{
    std::shared_ptr<Plane> p (new Plane());
    Ray r{Point(0, 1, 0), Vector(0, -1, 0)};

    std::vector<Intersection> xs = r.LocalIntersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}

TEST(Planes, ARayIntersectingAPlaneFormBelow)
{
    std::shared_ptr<Plane> p (new Plane());
    Ray r{Point(0, -1, 0), Vector(0, 1, 0)};

    std::vector<Intersection> xs = r.LocalIntersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}