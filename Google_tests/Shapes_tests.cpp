//
// Created by Jean-Luc von Nessen on 21.02.22.
//



#include "gtest/gtest.h"

#include "../cpp-Raytracer/CShape.h"
#include "../cpp-Raytracer/CShape.cpp"

#include "../cpp-Raytracer/CSphere.h"
//#include "../cpp-Raytracer/CSphere.cpp"

#include "../cpp-Raytracer/SIntersection.h"

#include "../cpp-Raytracer/CPlane.h"
#include "../cpp-Raytracer/CPlane.cpp"

#include "../cpp-Raytracer/CRay.h"

#include "../cpp-Raytracer/CCube.cpp"

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

TEST(Cubes, RayIntersectsCube_01)
{
    Cube_ptr c (new CCube());
    CRay r{Point(5, 0.5, 0), Vector(-1, 0, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_02)
{
    Cube_ptr c (new CCube());
    CRay r{Point(-5, 0.5, 0), Vector(1, 0, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_03)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0.5, 5, 0), Vector(0, -1, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_04)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0.5, -5, 0), Vector(0, 1, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_05)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0.5, 0, 5), Vector(0, 0, -1)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_06)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0.5, 0, -5), Vector(0, 0, 1)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_07)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0, 0.5, 0), Vector(0, 0, 1)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1);
    EXPECT_EQ(xs[1].t, 1);
}

TEST(Cubes, RayMissesCube_01)
{
    Cube_ptr c (new CCube());
    CRay r{Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_02)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_03)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_04)
{
    Cube_ptr c (new CCube());
    CRay r{Point(2, 0, 2), Vector(0, 0, -1)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_05)
{
    Cube_ptr c (new CCube());
    CRay r{Point(0, 2, 2), Vector(0, -1, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_06)
{
    Cube_ptr c (new CCube());
    CRay r{Point(2, 2, 0), Vector(-1, 0, 0)};

    std::vector<SIntersection> xs = r.LocalIntersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, NormalOnCubeSurface_01)
{
    Cube_ptr c (new CCube());
    Point p{1, 0.5, -0.8};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_02)
{
    Cube_ptr c (new CCube());
    Point p{-1, -0.2, 0.9};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(-1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_03)
{
    Cube_ptr c (new CCube());
    Point p{-0.4, 1, -0.1};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(0, 1, 0));
}

TEST(Cubes, NormalOnCubeSurface_04)
{
    Cube_ptr c (new CCube());
    Point p{0.3, -1, -0.7};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(0, -1, 0));
}

TEST(Cubes, NormalOnCubeSurface_05)
{
    Cube_ptr c (new CCube());
    Point p{-0.6, 0.3, 1};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(0, 0, 1));
}

TEST(Cubes, NormalOnCubeSurface_06)
{
    Cube_ptr c (new CCube());
    Point p{0.4, 0.4, -1};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(0, 0, -1));
}

TEST(Cubes, NormalOnCubeSurface_07)
{
    Cube_ptr c (new CCube());
    Point p{1, 1, 1};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_08)
{
    Cube_ptr c (new CCube());
    Point p{-1, -1, -1};
    Vector normal = c->LocalNormalAt(p);

    EXPECT_EQ(normal, Vector(-1, 0, 0));
}

