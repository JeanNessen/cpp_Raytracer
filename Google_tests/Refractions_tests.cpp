//
// Created by Jean-Luc von Nessen on 01.03.22.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/World.h"


Sphere_ptr GlassSphere()
{
    Sphere_ptr sphere{new Sphere()};
    sphere->GetMaterial().transparency = 1;
    sphere->GetMaterial().refractive_index = 1.5;

    return sphere;
}

TEST(Refractions, TransparencyAndRefractiveIndexOfDefaultMaterial)
{
    Material m{};

    EXPECT_EQ(m.transparency, 0);
    EXPECT_EQ(m.refractive_index, 1);
}

TEST(Refractions, HelperFunctionForProducingGlassSphere)
{
    Sphere_ptr s = GlassSphere();

    EXPECT_EQ(s->GetTransform(), Math::identiy_matrix);
    EXPECT_EQ(s->GetMaterial().transparency, 1);
    EXPECT_EQ(s->GetMaterial().refractive_index, 1.5);
}

TEST(Refractions, Findingn1Andn2AtVariousIntersections)
{
    Sphere_ptr A = GlassSphere();
    A->SetTransform(Math::Scaling(2, 2, 2));
    A->GetMaterial().refractive_index = 1.5;

    Sphere_ptr B = GlassSphere();
    B->SetTransform(Math::Translation(0, 0, -0.25));
    B->GetMaterial().refractive_index = 2.0;

    Sphere_ptr C = GlassSphere();
    C->SetTransform(Math::Translation(0, 0, 0.25));
    C->GetMaterial().refractive_index = 2.5;

    Ray r{Point(0, 0, -4), Vector(0, 0, 1)};

    std::vector<Intersection> xs{Intersection(2, A),
                                                 Intersection(2.75, B),
                                                 Intersection(3.25,C),
                                                 Intersection(4.75, B),
                                                 Intersection(5.25, C),
                                                 Intersection(6, A)};

    IntersectionComputations comps_01 = PrepareComputations(xs[0], r, xs);
    EXPECT_EQ(comps_01.n1, 1);
    EXPECT_EQ(comps_01.n2, 1.5);

    IntersectionComputations comps_02 = PrepareComputations(xs[1], r, xs);
    EXPECT_EQ(comps_02.n1, 1.5);
    EXPECT_EQ(comps_02.n2, 2);

    IntersectionComputations comps_03 = PrepareComputations(xs[2], r, xs);
    EXPECT_EQ(comps_03.n1, 2);
    EXPECT_EQ(comps_03.n2, 2.5);

    IntersectionComputations comps_04 = PrepareComputations(xs[3], r, xs);
    EXPECT_EQ(comps_04.n1, 2.5);
    EXPECT_EQ(comps_04.n2, 2.5);

    IntersectionComputations comps_05 = PrepareComputations(xs[4], r, xs);
    EXPECT_EQ(comps_05.n1, 2.5);
    EXPECT_EQ(comps_05.n2, 1.5);

    IntersectionComputations comps_06 = PrepareComputations(xs[5], r, xs);
    EXPECT_EQ(comps_06.n1, 1.5);
    EXPECT_EQ(comps_06.n2, 1);
}

TEST(Refractions, TheUnderPointIfOffsetBelowTheSurface)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

    Sphere_ptr shape = GlassSphere();
    shape->SetTransform(Math::Translation(0, 0, 1));
    Intersection i{5, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(comps.under_point.z > EPSILON/2);
    EXPECT_TRUE(comps.point.z < comps.under_point.z);
}

TEST(Refractions, TheRefractedColorWithOpaqueSurface)
{
    World w = DefaultWorld();
    Shape_ptr shape = w.GetWorldObjects()[0];
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::vector<Intersection> xs{Intersection(4, shape), Intersection(6, shape)};

    IntersectionComputations comps = PrepareComputations(xs[0], r, xs);
    Color c = w.RefractedColor(comps, 5);

    EXPECT_EQ(c, color::black);
}

TEST(Refractions, RefractedColorAtMaxRecursiveDepth)
{
    World w = DefaultWorld();
    Shape_ptr shape = w.GetWorldObjects()[0];
    shape->GetMaterial().transparency = 1;
    shape->GetMaterial().refractive_index = 1.5;
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::vector<Intersection> xs{Intersection(4, shape), Intersection(6, shape)};

    IntersectionComputations comps = PrepareComputations(xs[0], r, xs);
    Color c = w.RefractedColor(comps, 0);

    EXPECT_EQ(c, color::black);
}

TEST(Refractions, TheRefractedColorUnderTotalInternalReflection)
{
    World w = DefaultWorld();
    Shape_ptr shape = w.GetWorldObjects()[0];
    shape->GetMaterial().transparency = 1;
    shape->GetMaterial().refractive_index = 1.5;
    Ray r{Point(0, 0, sqrt(2)/2), Vector(0, 1, 0)};
    std::vector<Intersection> xs{Intersection(-sqrt(2)/2, shape), Intersection(sqrt(2)/2, shape)};

    IntersectionComputations comps = PrepareComputations(xs[1], r, xs);
    Color c = w.RefractedColor(comps, 5);

    EXPECT_EQ(c, color::black);
}

TEST(Refractions, RefractedColorWithRefractedRay)
{
    World w = DefaultWorld();

    Shape_ptr A = w.GetWorldObjects()[0];
    A->GetMaterial().ambient = 1;
    std::shared_ptr<Pattern> pat(new TestPattern(color::white, color::black));
    A->GetMaterial().SetPattern(pat);

    Shape_ptr B = w.GetWorldObjects()[1];
    B->GetMaterial().transparency = 1;
    B->GetMaterial().refractive_index = 1.5;

    Ray r{Point(0, 0, 0.1), Vector(0, 1, 0)};
    std::vector<Intersection> xs{Intersection(-0.9899, A),
                                 Intersection(-0.4899, B),
                                 Intersection(0.4899, B),
                                 Intersection(0.9899, A)};

    IntersectionComputations comps = PrepareComputations(xs[2], r, xs);
    Color c = w.RefractedColor(comps, 5);

    EXPECT_EQ(c, Color(0, 0.99888, 0.04725));

}

TEST(Refractions, ShadeHitWithTransparentMaterial)
{
    World w = DefaultWorld();

    Plane_ptr floor{new Plane()};
    floor->SetTransform(Math::Translation(0, -1, 0));
    floor->GetMaterial().transparency = 0.5;
    floor->GetMaterial().refractive_index = 1.5;
    w.AddObject(floor);

    Sphere_ptr ball{new Sphere()};
    ball->GetMaterial().color = color::red;
    ball->GetMaterial().ambient = 0.5;
    ball->SetTransform(Math::Translation(0, -3.5, -0.5));
    w.AddObject(ball);

    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2)};
    std::vector<Intersection> xs{Intersection(sqrt(2), floor)};

    IntersectionComputations comps = PrepareComputations(xs[0], r, xs);

    Color color = w.ShadeHit(comps, 5);

    EXPECT_EQ(color, Color(0.93642, 0.68642, 0.68642));
}

TEST(Refractions, SchlickApproximationUnterTotalInternalReflection)
{
    Sphere_ptr shape = GlassSphere();

    Ray r{Point(0, 0, sqrt(2)/2), Vector(0, 1, 0)};
    std::vector<Intersection> xs{Intersection(-sqrt(2)/2, shape), Intersection(sqrt(2)/2, shape)};

    IntersectionComputations comps = PrepareComputations(xs[1], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 1));
}

TEST(Refractions, SchlickApproximationWithPerpendicularViewingAngle) {
    Shape_ptr shape = GlassSphere();
    Ray r{Point(0, 0, 0), Vector(0, 1, 0)};
    std::vector<Intersection> xs{Intersection(-1, shape), Intersection(1, shape)};

    IntersectionComputations comps = PrepareComputations(xs[1], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 0.04));
}

TEST(Refractions, SchlickApproximationWithSmallAngleAndn2Biggern1)
{
    Shape_ptr shape = GlassSphere();

    Ray r{Point(0, 0.99, -2), Vector(0, 0, 1)};
    std::vector<Intersection> xs{Intersection(1.8589, shape)};

    IntersectionComputations comps = PrepareComputations(xs[0], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 0.48873));
}

TEST(Refractions, ShadeHitWithAReflectiveTransparentMaterial)
{
    World w = DefaultWorld();

    Plane_ptr floor{new Plane()};
    floor->SetTransform(Math::Translation(0, -1, 0));
    floor->GetMaterial().reflective = 0.5;
    floor->GetMaterial().transparency = 0.5;
    floor->GetMaterial().refractive_index = 1.5;
    w.AddObject(floor);

    Sphere_ptr ball{new Sphere()};
    ball->GetMaterial().color = color::red;
    ball->GetMaterial().ambient = 0.5;
    ball->SetTransform(Math::Translation(0, -3.5, -0.5));
    w.AddObject(ball);

    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2)};
    std::vector<Intersection> xs{Intersection(sqrt(2), floor)};

    IntersectionComputations comps = PrepareComputations(xs[0], r, xs);

    Color color = w.ShadeHit(comps, 5);

    EXPECT_EQ(color, Color(0.93391, 0.69643, 0.69243));
}