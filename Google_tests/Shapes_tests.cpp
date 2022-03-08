//
// Created by Jean-Luc von Nessen on 21.02.22.
//



#include "gtest/gtest.h"

#include "../cpp-Raytracer/CShape.h"
#include "../cpp-Raytracer/CShape.cpp"

#include "../cpp-Raytracer/CSphere.h"
//#include "../cpp-Raytracer/CSphere.cpp"

#include "../cpp-Raytracer/CPlane.h"
#include "../cpp-Raytracer/CPlane.cpp"

#include "../cpp-Raytracer/CRay.h"

#include <vector>

TEST(Spheres, TheDefaultTransformation)
{
    CSphere s{};

    EXPECT_EQ(s.GetTransform(), Math::identiy_matrix);
}

TEST(Spheres, AssigningATransformation)
{
    CSphere s{};

    s.SetTransform(Math::Translation(2, 3, 4));

    EXPECT_EQ(s.GetTransform(), Math::Translation(2, 3, 4));
}

TEST(Spheres, TheDefaultMaterial)
{
    CSphere s{};

    EXPECT_EQ(s.GetMaterial(), CMaterial{});
}

TEST(Spheres, AssigningAMaterial)
{
    CSphere s{};
    CMaterial m{};
    m.ambient = 1;

    s.SetMaterial(m);

    EXPECT_EQ(s.GetMaterial(), m);
}

TEST(Spheres, IntersectingAScaledSphereWithARay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere_ptr s (new CSphere());

    s->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(s->saved_ray_origin, Point(0, 0, -2.5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Spheres, IntersectingATranslatedSphereWithARay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere_ptr s(new CSphere());

    s->SetTransform(Math::Translation(5, 0, 0));
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(s->saved_ray_origin, Point(-5, 0, -5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 1));
}

TEST(Planes, TheDefaultTransformation)
{
    CPlane p{};

    EXPECT_EQ(p.GetTransform(), Math::identiy_matrix);
}

TEST(Planes, AssigningATransformation)
{
    CPlane p{};

    p.SetTransform(Math::Translation(2, 3, 4));

    EXPECT_EQ(p.GetTransform(), Math::Translation(2, 3, 4));
}

TEST(Planes, TheDefaultMaterial)
{
    CPlane p{};

    EXPECT_EQ(p.GetMaterial(), CMaterial{});
}

TEST(Planes, AssigningAMaterial)
{
    CPlane p{};
    CMaterial m{};
    m.ambient = 1;

    p.SetMaterial(m);

    EXPECT_EQ(p.GetMaterial(), m);
}

TEST(Planes, IntersectingAScaledPlaneWithARay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Plane_ptr p (new CPlane());

    p->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<SIntersection> xs = r.Intersect(p);

    EXPECT_EQ(p->saved_ray_origin, Point(0, 0, -2.5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Planes, IntersectingATranslatedPlaneWithARay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Plane_ptr p (new CPlane());

    p->SetTransform(Math::Translation(5, 0, 0));
    std::vector<SIntersection> xs = r.Intersect(p);

    EXPECT_EQ(p->saved_ray_origin, Point(-5, 0, -5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 1));
}

TEST(Planes, TheNormalOfAPlaneIsConstantEverywhere)
{
    CPlane p{};

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
    Plane_ptr p (new CPlane());
    CRay r{Point(0, 10, 10), Vector(0, 0, 1)};

    std::vector<SIntersection> xs = r.LocalIntersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, IntersectWithACoplanarRay)
{
    Plane_ptr p (new CPlane());
    CRay r{Point(0, 0, 0), Vector(0, 0, 1)};

    std::vector<SIntersection> xs = r.LocalIntersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, ARayIntersectingAPlaneFormAbove)
{
    Plane_ptr p (new CPlane());
    CRay r{Point(0, 1, 0), Vector(0, -1, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}

TEST(Planes, ARayIntersectingAPlaneFormBelow)
{
    Plane_ptr p (new CPlane());
    CRay r{Point(0, -1, 0), Vector(0, 1, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}