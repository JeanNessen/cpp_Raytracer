//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Ray.h"
#include "../cpp-Raytracer/Ray.cpp"

#include "../cpp-Raytracer/Sphere.h"
#include "../cpp-Raytracer/Sphere.cpp"

TEST(RayTracing, CreatingARay)
{
    Point origin{ 1, 2, 3 };
    Vector direction{ 4, 5, 6 };
    Ray r{ origin, direction };

    EXPECT_TRUE(Math::Equal(origin, r.origin));
    EXPECT_TRUE(Math::Equal(direction, r.direction));
}

TEST(RayTracing, ComputingPointFromDistance)
{
    Ray r{ Point{2, 3, 4}, Vector{1, 0, 0} };

    Point pos1{2, 3, 4};
    Point pos2{3, 3, 4};
    Point pos3{1, 3 ,4};
    Point pos4{4.5, 3, 4};

    EXPECT_TRUE(Math::Equal(r.Position(0), pos1));
    EXPECT_TRUE(Math::Equal(r.Position(1), pos2));
    EXPECT_TRUE(Math::Equal(r.Position(-1), pos3));
    EXPECT_TRUE(Math::Equal(r.Position(2.5), pos4));
}

TEST(RayTracing, ComparingSpheres)
{
    Sphere s1{ 0 };
    Sphere s2{ 1 };

    EXPECT_EQ(s1, s1);
    EXPECT_NE(s1, s2);
}

TEST(RayTracing, ComparingIntersections)
{
    Sphere s1{ 0 };
    Sphere s2{ 1 };

    Intersection i1{ 1.0f, s1 };
    Intersection i2{ 1.0f, s2 };
    Intersection i3{ 2.0f, s1 };
    Intersection i4{ 2.0f, s2 };

    EXPECT_EQ(i1, i1);
    EXPECT_NE(i1, i2);
    EXPECT_NE(i1, i3);
    EXPECT_NE(i1, i4);
}

TEST(RayTracing, RaySphereIntersection2Points)
{
    Ray r{ Point{0,0,-5}, Vector{0,0,1} };
    Sphere s{ 0 };

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 6.0f));
}

TEST(RayTracing, RayIntersectsSphereTangent)
{
    Ray r{ Point(0, 1, -5), Vector(0, 0, 1) };
    Sphere s{0};

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 5.0));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.0));
}

TEST(RayTracing, RayMissesSphere)
{
    Ray r{ Point(0, 2, -5), Vector(0, 0, 1) };
    Sphere s{ 0 };

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 0));
}

TEST(RayTracing, RayOriginInSphere)
{
    Ray r{ Point(0, 0, 0), Vector(0, 0, 1) };
    Sphere s{ 0 };

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -1.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 1.0f));
}

TEST(RayTracing, RayOriginBehindSphere)
{
    Ray r{ Point(0, 0, 5), Vector(0, 0, 1) };
    Sphere s{ 0 };

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -6.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, -4.0f));
}

TEST(RayTracing, IntersectionEncapsulatesAnObject)
{
    Sphere s{ 0 };
    Intersection I1{ 1.0f, s };
    Intersection I2{ 2.0f, s };

    std::vector<Intersection> xs = Intersections({ I1, I2 });

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
}

TEST(RayTracing, Aggregating5Intersections)
{
    Sphere s1{ 0 };
    Sphere s2{ 1 };
    Sphere s3{ 2 };
    Intersection I1{ 1.0f, s1 };
    Intersection I2{ 2.0f, s1 };
    Intersection I3{ 3.0f, s2 };
    Intersection I4{ 4.0f, s2 };
    Intersection I5{ 5.0f, s3 };

    std::vector<Intersection> xs = Intersections({ I1, I2, I3, I4, I5 });

    EXPECT_TRUE(Math::Equal(xs.size(), 5));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
    EXPECT_TRUE(Math::Equal(I3.t, 3.0f));
    EXPECT_TRUE(Math::Equal(I4.t, 4.0f));
    EXPECT_TRUE(Math::Equal(I5.t, 5.0f));
}

TEST(RayTracing, IntersectSetsTheObjectOnTheIntersection)
{
    Ray r{ Point(0, 0, 5), Vector(0, 0, 1) };
    Sphere s{ 0 };
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs[0].object, s);
    EXPECT_EQ(xs[1].object, s);
}

TEST(RayTracing, HitWhenAllIntersectionsHavePositiveT)
{
    Sphere s{ 0 };
    Intersection i1{ 1, s };
    Intersection i2{ 2, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(*i, i1);
}

TEST(RayTracing, HitWhenSomeIntersectionsHaveNegativeT)
{
    Sphere s{ 0 };
    Intersection i1{ -1, s };
    Intersection i2{ 1, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(*i, i2);
}

TEST(RayTracing, HitWhenAllIntersectionsAreNegative)
{
    Sphere s{ 0 };
    Intersection i1{ -1, s };
    Intersection i2{ -2, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(i, nullptr);
}

TEST(RayTracing, HitIsAlwaysLowestNotNegativeIntersection)
{
    Sphere s{ 0 };
    Intersection i1{ 5, s };
    Intersection i2{ 7, s };
    Intersection i3{ -3, s };
    Intersection i4{ 2, s };

    std::vector<Intersection> xs{ i1, i2, i3, i4 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(*i, i4);
}

TEST(RayTracing, TranslatingARay)
{
    Ray r{ Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Translation(3, 4, 5);

    Ray r2 = r.Transform(m);

    EXPECT_EQ(r2.origin, Point(4, 6, 8));
    EXPECT_EQ(r2.direction, Vector(0, 1, 0));
}

TEST(RayTracing, ScalingARay)
{
    Ray r{ Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Scaling(2, 3, 4);

    Ray r2 = r.Transform(m);

    EXPECT_EQ(r2.origin, Point(2, 6, 12));
    EXPECT_EQ(r2.direction, Vector(0, 3, 0));
}

TEST(RayTracing, SphereDefaultTransformation)
{
    Sphere s{0};

    EXPECT_EQ(s.GetTransform(), Math::identiy_matrix);
}

TEST(RayTracing, ChangingSphereTransform)
{
    Sphere s{ 0 };
    Matrix4 t = Math::Translation(2, 3, 4);

    s.SetTransform(t);

    EXPECT_EQ(s.GetTransform(), t);
}

TEST(RayTracing, IntersectingScaledSphereWithRay)
{
    Ray r{ Point(0,0,-5), Vector(0,0,1) };
    Sphere s{ 0 };

    s.SetTransform(Math::Scaling(2, 2, 2));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 3.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 7.0f));
}

TEST(RayTracing, IntersectingTranslatedSphereWithRay)
{
    Ray r{ Point(0,0,-5), Vector(0,0,1) };
    Sphere s{ 0 };

    s.SetTransform(Math::Translation(5, 0, 0));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 0);
}