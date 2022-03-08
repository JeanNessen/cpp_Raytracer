//
// Created by Jean-Luc von Nessen on 25.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/CMaterial.h"

#include "../cpp-Raytracer/CPlane.h"
#include "../cpp-Raytracer/SIntersectionComputations.h"
#include "../cpp-Raytracer/CWorld.h"

TEST(Reflections, ReflectivityForDefaultMaterial)
{
    CMaterial m{};

    EXPECT_EQ(m.reflective, 0);
}

TEST(Reflections, PrecomputingReflectionVector)
{
    Plane_ptr plane (new CPlane());
    CRay r{Point(0, 1, -1), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    SIntersection i{sqrt(2), plane};

    SIntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(Math::Equal(comps.reflect_v, Vector(0, sqrt(2)/2, sqrt(2)/2)));
}

TEST(Reflections, ReflectedColorForNonreflectiveMaterial)
{
    CWorld w = DefaultWorld();
    CRay r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere_ptr shape = dynamic_pointer_cast<CSphere>(w.GetWorldObjects()[1]);
    shape->GetMaterial().ambient = 1;
    SIntersection i{1, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.CalculateReflectedColor(comps);

    EXPECT_EQ(c, CColor(0, 0, 0));
}

TEST(Reflections, ReflectedColorForReflectiveMaterial)
{
    CWorld w = DefaultWorld();
    Plane_ptr shape (new CPlane());
    shape->GetMaterial().reflective = 0.5;
    shape->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(shape);
    CRay r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    SIntersection i{sqrt(2), shape};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.CalculateReflectedColor(comps);

    EXPECT_EQ(c, CColor(0.19032, 0.2379, 0.14274));
}

TEST(Reflections, ShadeHitWithReflectiveMaterial)
{
    CWorld w = DefaultWorld();
    Plane_ptr shape (new CPlane());
    shape->GetMaterial().reflective = 0.5;
    shape->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(shape);
    CRay r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    SIntersection i{sqrt(2), shape};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.ShadeHit(comps);

    EXPECT_EQ(c, CColor(0.87677, 0.92436, 0.82918));
}

TEST(Reflections, ColorAtWithMutuallyReflectiveSurfaces)
{
    CWorld w{};
    w.AddLight(SPointLight(color::white, Point(0, 0, 0)));

    Plane_ptr lower(new CPlane());
    lower->GetMaterial().reflective = 1;
    lower->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(lower);

    Plane_ptr upper(new CPlane());
    upper->GetMaterial().reflective = 1;
    upper->SetTransform(Math::Translation(0, 1, 0));
    w.AddObject(upper);

    CRay r{Point(0, 0, 0), Vector(0, 1, 0)};

    CColor c = w.CalculateColorAt(r);
}

TEST(Reflections, TheReflectedColorAtMaximumRecursiveDepth)
{
    CWorld w = DefaultWorld();
    Plane_ptr plane(new CPlane());
    plane->GetMaterial().reflective = 0.5;
    plane->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(plane);
    CRay r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    SIntersection i{sqrt(2), plane};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.CalculateReflectedColor(comps, 0);

    EXPECT_EQ(c, color::black);

}