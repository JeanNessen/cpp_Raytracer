//
// Created by Jean-Luc von Nessen on 25.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Material.h"

#include "../cpp-Raytracer/Plane.h"
#include "../cpp-Raytracer/IntersectionComputations.h"
#include "../cpp-Raytracer/World.h"

TEST(Reflections, ReflectivityForDefaultMaterial)
{
    Material m{};

    EXPECT_EQ(m.reflective, 0);
}

TEST(Reflections, PrecomputingReflectionVector)
{
    Plane_ptr plane (new Plane());
    Ray r{Point(0, 1, -1), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Intersection i{sqrt(2), plane};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(Math::Equal(comps.reflect_v, Vector(0, sqrt(2)/2, sqrt(2)/2)));
}

TEST(Reflections, ReflectedColorForNonreflectiveMaterial)
{
    World w = DefaultWorld();
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere_ptr shape = dynamic_pointer_cast<Sphere>(w.GetWorldObjects()[1]);
    shape->GetMaterial().ambient = 1;
    Intersection i{1, shape};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.CalculateReflectedColor(comps);

    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(Reflections, ReflectedColorForReflectiveMaterial)
{
    World w = DefaultWorld();
    Plane_ptr shape (new Plane());
    shape->GetMaterial().reflective = 0.5;
    shape->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(shape);
    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Intersection i{sqrt(2), shape};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.CalculateReflectedColor(comps);

    EXPECT_EQ(c, Color(0.19032, 0.2379, 0.14274));
}

TEST(Reflections, ShadeHitWithReflectiveMaterial)
{
    World w = DefaultWorld();
    Plane_ptr shape (new Plane());
    shape->GetMaterial().reflective = 0.5;
    shape->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(shape);
    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Intersection i{sqrt(2), shape};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.ShadeHit(comps);

    EXPECT_EQ(c, Color(0.87677, 0.92436, 0.82918));
}

TEST(Reflections, ColorAtWithMutuallyReflectiveSurfaces)
{
    World w{};
    w.AddLight(PointLight(color::white, Point(0, 0, 0)));

    Plane_ptr lower(new Plane());
    lower->GetMaterial().reflective = 1;
    lower->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(lower);

    Plane_ptr upper(new Plane());
    upper->GetMaterial().reflective = 1;
    upper->SetTransform(Math::Translation(0, 1, 0));
    w.AddObject(upper);

    Ray r{Point(0, 0, 0), Vector(0, 1, 0)};

    Color c = w.CalculateColorAt(r);
}

TEST(Reflections, TheReflectedColorAtMaximumRecursiveDepth)
{
    World w = DefaultWorld();
    Plane_ptr plane(new Plane());
    plane->GetMaterial().reflective = 0.5;
    plane->SetTransform(Math::Translation(0, -1, 0));
    w.AddObject(plane);
    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Intersection i{sqrt(2), plane};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.CalculateReflectedColor(comps, 0);

    EXPECT_EQ(c, color::black);

}