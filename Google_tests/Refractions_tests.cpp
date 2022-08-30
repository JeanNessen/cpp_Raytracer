//
// Created by Jean-Luc von Nessen on 01.03.22.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/World.h"


sphere_ptr GlassSphere()
{
    sphere_ptr sphere{new Sphere()};
    sphere->get_material().transparency = 1;
    sphere->get_material().refractive_index = 1.5;

    return sphere;
}

TEST(Refractions, TransparencyAndRefractiveIndexOfDefaultMaterial)
{
    material m{};

    EXPECT_EQ(m.transparency, 0);
    EXPECT_EQ(m.refractive_index, 1);
}

TEST(Refractions, HelperFunctionForProducingGlassSphere)
{
    sphere_ptr s = GlassSphere();

    EXPECT_EQ(s->get_transform(), Math::identiy_matrix);
    EXPECT_EQ(s->get_material().transparency, 1);
    EXPECT_EQ(s->get_material().refractive_index, 1.5);
}

TEST(Refractions, Findingn1Andn2AtVariousIntersections)
{
    sphere_ptr A = GlassSphere();
    A->set_transform(Math::Scaling(2, 2, 2));
    A->get_material().refractive_index = 1.5;

    sphere_ptr B = GlassSphere();
    B->set_transform(Math::Translation(0, 0, -0.25));
    B->get_material().refractive_index = 2.0;

    sphere_ptr C = GlassSphere();
    C->set_transform(Math::Translation(0, 0, 0.25));
    C->get_material().refractive_index = 2.5;

    ray r{point(0, 0, -4), vector(0, 0, 1)};

    std::vector<intersection> xs{intersection(2, A),
                                  intersection(2.75, B),
                                  intersection(3.25, C),
                                  intersection(4.75, B),
                                  intersection(5.25, C),
                                  intersection(6, A)};

    intersection_computations comps_01 = PrepareComputations(xs[0], r, xs);
    EXPECT_EQ(comps_01.n1, 1);
    EXPECT_EQ(comps_01.n2, 1.5);

    intersection_computations comps_02 = PrepareComputations(xs[1], r, xs);
    EXPECT_EQ(comps_02.n1, 1.5);
    EXPECT_EQ(comps_02.n2, 2);

    intersection_computations comps_03 = PrepareComputations(xs[2], r, xs);
    EXPECT_EQ(comps_03.n1, 2);
    EXPECT_EQ(comps_03.n2, 2.5);

    intersection_computations comps_04 = PrepareComputations(xs[3], r, xs);
    EXPECT_EQ(comps_04.n1, 2.5);
    EXPECT_EQ(comps_04.n2, 2.5);

    intersection_computations comps_05 = PrepareComputations(xs[4], r, xs);
    EXPECT_EQ(comps_05.n1, 2.5);
    EXPECT_EQ(comps_05.n2, 1.5);

    intersection_computations comps_06 = PrepareComputations(xs[5], r, xs);
    EXPECT_EQ(comps_06.n1, 1.5);
    EXPECT_EQ(comps_06.n2, 1);
}

TEST(Refractions, TheUnderPointIfOffsetBelowTheSurface)
{
    ray r{point(0, 0, -5), vector(0, 0, 1)};

    sphere_ptr shape = GlassSphere();
    shape->set_transform(Math::Translation(0, 0, 1));
    intersection i{5, shape};

    intersection_computations comps = PrepareComputations(i, r);

    EXPECT_TRUE(comps.under_point.z > EPSILON/2);
    EXPECT_TRUE(comps.intersect_point.z < comps.under_point.z);
}

TEST(Refractions, TheRefractedColorWithOpaqueSurface)
{
    World w = DefaultWorld();
    shape_ptr shape = w.get_world_objects()[0];
    ray r{point(0, 0, -5), vector(0, 0, 1)};
    std::vector<intersection> xs{intersection(4, shape), intersection(6, shape)};

    intersection_computations comps = PrepareComputations(xs[0], r, xs);
    color c = w.calculate_refracted_color(comps, 5);

    EXPECT_EQ(c, colors::black);
}

TEST(Refractions, RefractedColorAtMaxRecursiveDepth)
{
    World w = DefaultWorld();
    shape_ptr shape = w.get_world_objects()[0];
    shape->get_material().transparency = 1;
    shape->get_material().refractive_index = 1.5;
    ray r{point(0, 0, -5), vector(0, 0, 1)};
    std::vector<intersection> xs{intersection(4, shape), intersection(6, shape)};

    intersection_computations comps = PrepareComputations(xs[0], r, xs);
    color c = w.calculate_refracted_color(comps, 0);

    EXPECT_EQ(c, colors::black);
}

TEST(Refractions, TheRefractedColorUnderTotalInternalReflection)
{
    World w = DefaultWorld();
    shape_ptr shape = w.get_world_objects()[0];
    shape->get_material().transparency = 1;
    shape->get_material().refractive_index = 1.5;
    ray r{point(0, 0, sqrt(2) / 2), vector(0, 1, 0)};
    std::vector<intersection> xs{intersection(-sqrt(2) / 2, shape), intersection(sqrt(2) / 2, shape)};

    intersection_computations comps = PrepareComputations(xs[1], r, xs);
    color c = w.calculate_refracted_color(comps, 5);

    EXPECT_EQ(c, colors::black);
}

TEST(Refractions, RefractedColorWithRefractedRay)
{
    World w = DefaultWorld();

    shape_ptr A = w.get_world_objects()[0];
    A->get_material().ambient = 1;
    std::shared_ptr<pattern> pat(new test_pattern(colors::white, colors::black));
    A->get_material().SetPattern(pat);

    shape_ptr B = w.get_world_objects()[1];
    B->get_material().transparency = 1;
    B->get_material().refractive_index = 1.5;

    ray r{point(0, 0, 0.1), vector(0, 1, 0)};
    std::vector<intersection> xs{intersection(-0.9899, A),
                                  intersection(-0.4899, B),
                                  intersection(0.4899, B),
                                  intersection(0.9899, A)};

    intersection_computations comps = PrepareComputations(xs[2], r, xs);
    color c = w.calculate_refracted_color(comps, 5);

    EXPECT_EQ(c, color(0, 0.99888, 0.04725));

}

TEST(Refractions, ShadeHitWithTransparentMaterial)
{
    World w = DefaultWorld();

    plane_ptr floor{new plane()};
    floor->set_transform(Math::Translation(0, -1, 0));
    floor->get_material().transparency = 0.5;
    floor->get_material().refractive_index = 1.5;
    w.add_object(floor);

    sphere_ptr ball{new Sphere()};
    ball->get_material().color = colors::red;
    ball->get_material().ambient = 0.5;
    ball->set_transform(Math::Translation(0, -3.5, -0.5));
    w.add_object(ball);

    ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    std::vector<intersection> xs{intersection(sqrt(2), floor)};

    intersection_computations comps = PrepareComputations(xs[0], r, xs);

    color refraction_color = w.shade_hit(comps, 5);

    EXPECT_EQ(refraction_color, color(0.93642, 0.68642, 0.68642));
}

TEST(Refractions, SchlickApproximationUnterTotalInternalReflection)
{
    sphere_ptr shape = GlassSphere();

    ray r{point(0, 0, sqrt(2) / 2), vector(0, 1, 0)};
    std::vector<intersection> xs{intersection(-sqrt(2) / 2, shape), intersection(sqrt(2) / 2, shape)};

    intersection_computations comps = PrepareComputations(xs[1], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 1));
}

TEST(Refractions, SchlickApproximationWithPerpendicularViewingAngle) {
    shape_ptr shape = GlassSphere();
    ray r{point(0, 0, 0), vector(0, 1, 0)};
    std::vector<intersection> xs{intersection(-1, shape), intersection(1, shape)};

    intersection_computations comps = PrepareComputations(xs[1], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 0.04));
}

TEST(Refractions, SchlickApproximationWithSmallAngleAndn2Biggern1)
{
    shape_ptr shape = GlassSphere();

    ray r{point(0, 0.99, -2), vector(0, 0, 1)};
    std::vector<intersection> xs{intersection(1.8589, shape)};

    intersection_computations comps = PrepareComputations(xs[0], r, xs);
    double reflectance = Schlick(comps);

    EXPECT_TRUE(Math::Equal(reflectance, 0.48873));
}

TEST(Refractions, ShadeHitWithAReflectiveTransparentMaterial)
{
    World w = DefaultWorld();

    plane_ptr floor{new plane()};
    floor->set_transform(Math::Translation(0, -1, 0));
    floor->get_material().reflective = 0.5;
    floor->get_material().transparency = 0.5;
    floor->get_material().refractive_index = 1.5;
    w.add_object(floor);

    sphere_ptr ball{new Sphere()};
    ball->get_material().color = colors::red;
    ball->get_material().ambient = 0.5;
    ball->set_transform(Math::Translation(0, -3.5, -0.5));
    w.add_object(ball);

    ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    std::vector<intersection> xs{intersection(sqrt(2), floor)};

    intersection_computations comps = PrepareComputations(xs[0], r, xs);

    color floor_color = w.shade_hit(comps, 5);

    EXPECT_EQ(floor_color, color(0.93391, 0.69643, 0.69243));
}