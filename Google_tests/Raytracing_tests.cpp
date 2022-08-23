//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Ray.h"
#include "../cpp-Raytracer/Ray.cpp"

#include "../cpp-Raytracer/Intersection.h"
#include "../cpp-Raytracer/Intersection.cpp"

//#include "../cpp-Raytracer/IntersectionComputations.h"
#include "../cpp-Raytracer/IntersectionComputations.cpp"

#include "../cpp-Raytracer/Shapes/shape.h"
//#include "../cpp-Raytracer/shape.cpp"

#include "../cpp-Raytracer/Shapes/Sphere.h"
#include "../cpp-Raytracer/Shapes/Sphere.cpp"

#include "../cpp-Raytracer/color.h"

#include "../cpp-Raytracer/Light.h"
#include "../cpp-Raytracer/Light.cpp"

#include "../cpp-Raytracer/Material.h"
#include "../cpp-Raytracer/Material.cpp"

#include "../cpp-Raytracer/Pattern.h"
#include "../cpp-Raytracer/Pattern.cpp"

#include <limits>

TEST(RayTracing, CreatingARay)
{
    Point origin{ 1, 2, 3 };
    Vector direction{ 4, 5, 6 };
    ray r{origin, direction };

    EXPECT_TRUE(Math::Equal(origin, r.origin));
    EXPECT_TRUE(Math::Equal(direction, r.direction));
}

TEST(RayTracing, ComputingPointFromDistance)
{
    ray r{Point{2, 3, 4}, Vector{1, 0, 0} };

    Point pos1{2, 3, 4};
    Point pos2{3, 3, 4};
    Point pos3{1, 3 ,4};
    Point pos4{4.5, 3, 4};

    EXPECT_TRUE(Math::Equal(r.position(0), pos1));
    EXPECT_TRUE(Math::Equal(r.position(1), pos2));
    EXPECT_TRUE(Math::Equal(r.position(-1), pos3));
    EXPECT_TRUE(Math::Equal(r.position(2.5), pos4));
}

TEST(RayTracing, ComparingSpheres)
{
    Sphere s1{};
    Sphere s2{};

    EXPECT_EQ(s1, s1);
    EXPECT_NE(s1, s2);
}

TEST(RayTracing, ComparingIntersections)
{
    sphere_ptr s1 (new Sphere());
    sphere_ptr s2 (new Sphere());

    intersection i1{1.0f, s1 };
    intersection i2{1.0f, s2 };
    intersection i3{2.0f, s1 };
    intersection i4{2.0f, s2 };

    EXPECT_EQ(i1, i1);
    EXPECT_NE(i1, i2);
    EXPECT_NE(i1, i3);
    EXPECT_NE(i1, i4);
}

TEST(RayTracing, RaySphereIntersection2Points)
{
    ray r{Point{0, 0, -5}, Vector{0, 0, 1} };
    sphere_ptr s (new Sphere());

    std::vector<intersection> xs = r.intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 6.0f));
}

TEST(RayTracing, RayIntersectsSphereTangent)
{
    ray r{Point(0, 1, -5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    std::vector<intersection> xs = r.intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 5.0));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.0));
}

TEST(RayTracing, RayMissesSphere)
{
    ray r{Point(0, 2, -5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    std::vector<intersection> xs = r.intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 0));
}

TEST(RayTracing, RayOriginInSphere)
{
    ray r{Point(0, 0, 0), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    std::vector<intersection> xs = r.intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -1.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 1.0f));
}

TEST(RayTracing, RayOriginBehindSphere)
{
    ray r{Point(0, 0, 5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    std::vector<intersection> xs = r.intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -6.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, -4.0f));
}

TEST(RayTracing, IntersectionEncapsulatesAnObject)
{
    sphere_ptr s (new Sphere());
    intersection I1{1.0f, s };
    intersection I2{2.0f, s };

    std::vector<intersection> xs{I1, I2 };

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
}

TEST(RayTracing, Aggregating5Intersections)
{
    sphere_ptr s1 (new Sphere());
    sphere_ptr s2 (new Sphere());
    sphere_ptr s3 (new Sphere());
    intersection I1{1.0f, s1 };
    intersection I2{2.0f, s1 };
    intersection I3{3.0f, s2 };
    intersection I4{4.0f, s2 };
    intersection I5{5.0f, s3 };

    std::vector<intersection> xs{I1, I2, I3, I4, I5 };

    EXPECT_TRUE(Math::Equal(xs.size(), 5));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
    EXPECT_TRUE(Math::Equal(I3.t, 3.0f));
    EXPECT_TRUE(Math::Equal(I4.t, 4.0f));
    EXPECT_TRUE(Math::Equal(I5.t, 5.0f));
}

TEST(RayTracing, IntersectSetsTheObjectOnTheIntersection)
{
    ray r{Point(0, 0, 5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(xs[0].object, s);
    EXPECT_EQ(xs[1].object, s);
}

TEST(RayTracing, HitWhenAllIntersectionsHavePositiveT)
{
    sphere_ptr s (new Sphere());
    intersection i1{1, s };
    intersection i2{2, s };
    std::vector<intersection> xs{i2, i1 };

    intersection *i = hit(xs);

    EXPECT_EQ(*i, i1);
}

TEST(RayTracing, HitWhenSomeIntersectionsHaveNegativeT)
{
    sphere_ptr s(new Sphere());
    intersection i1{-1, s };
    intersection i2{1, s };
    std::vector<intersection> xs{i2, i1 };

    intersection *i = hit(xs);

    EXPECT_EQ(*i, i2);
}

TEST(RayTracing, HitWhenAllIntersectionsAreNegative)
{
    sphere_ptr s (new Sphere());
    intersection i1{-1, s };
    intersection i2{-2, s };
    std::vector<intersection> xs{i2, i1 };

    intersection *i = hit(xs);

    EXPECT_EQ(i, nullptr);
}

TEST(RayTracing, HitIsAlwaysLowestNotNegativeIntersection)
{
    sphere_ptr s (new Sphere());
    intersection i1{5, s };
    intersection i2{7, s };
    intersection i3{-3, s };
    intersection i4{2, s };

    std::vector<intersection> xs{i1, i2, i3, i4 };

    intersection *i = hit(xs);

    EXPECT_EQ(*i, i4);
}

TEST(RayTracing, TranslatingARay)
{
    ray r{Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Translation(3, 4, 5);

    ray r2 = r.transform(m);

    EXPECT_EQ(r2.origin, Point(4, 6, 8));
    EXPECT_EQ(r2.direction, Vector(0, 1, 0));
}

TEST(RayTracing, ScalingARay)
{
    ray r{Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Scaling(2, 3, 4);

    ray r2 = r.transform(m);

    EXPECT_EQ(r2.origin, Point(2, 6, 12));
    EXPECT_EQ(r2.direction, Vector(0, 3, 0));
}

TEST(RayTracing, SphereDefaultTransformation)
{
    Sphere s{};

    EXPECT_EQ(s.get_transform(), Math::identiy_matrix);
}

TEST(RayTracing, ChangingSphereTransform)
{
    Sphere s{};
    Matrix4 t = Math::Translation(2, 3, 4);

    s.set_transform(t);

    EXPECT_EQ(s.get_transform(), t);
}

TEST(RayTracing, IntersectingScaledSphereWithRay)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    s->set_transform(Math::Scaling(2, 2, 2));
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 3.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 7.0f));
}

TEST(RayTracing, IntersectingScaledSphereWithRay2)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    s->set_transform(Math::Scaling(0.5, 0.5, 0.5));
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.5f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.5f));
}

TEST(RayTracing, IntersectingTranslatedSphereWithRay)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1) };
    sphere_ptr s (new Sphere());

    s->set_transform(Math::Translation(5, 0, 0));
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(xs.size(), 0);
}

TEST(RayTracing, NormalOnSphereX)
{
    sphere_ptr s (new Sphere());
    Vector n = s->normal_at(Point(1, 0, 0));

    EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(RayTracing, NormalOnSphereY)
{
    sphere_ptr s (new Sphere());
    Vector n = s->normal_at(Point(0, 1, 0));

    EXPECT_EQ(n, Vector(0, 1, 0));
}

TEST(RayTracing, NormalOnSphereZ)
{
    sphere_ptr s (new Sphere());
    Vector n = s->normal_at(Point(0, 0, 1));

    EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(RayTracing, NormalNonaxial)
{
    sphere_ptr s (new Sphere());
    Vector n = s->normal_at(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, Vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));
}

TEST(RayTracing, NormalVectorIsNormalized)
{
    sphere_ptr s (new Sphere());
    Vector n = s->normal_at(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, n.normalized());
}

TEST(RayTracing, NormalOnTranslatedSphere)
{
    sphere_ptr s (new Sphere());
    s->set_transform(Math::Translation(0, 1, 0));
    Vector n = s->normal_at(Point(0, 1.70711, -0.70711));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.70711, -0.70711)));
}

TEST(RayTracing, NormalOnTransformedSphere)
{
    Sphere s{};
    Matrix4 m = Math::Scaling(1, 0.5, 1) * Math::Rotation_Z(M_PI/5);

    s.set_transform(m);
    Vector n = s.normal_at(Point(0, std::sqrt(2)/2, -std::sqrt(2)/2));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.97014, -0.24254)));
}

TEST(RayTracing, PrecomputingStateOfAnIntersection)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    sphere_ptr shape (new Sphere());
    intersection i{4, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, Point(0, 0, -1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1));
}

TEST(RayTracing, HitWhenIntersectionOccursOnOutside)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    sphere_ptr shape (new Sphere());
    intersection i{4, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_FALSE(comps.inside);
}

TEST(RayTracing, HitWhenIntersectionOccursOnInside)
{
    ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    sphere_ptr shape (new Sphere());
    intersection i{1, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.point, Point(0, 0, 1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1)); //inverted because the hit occured on the inside
}

TEST(Lighting, PointLightPositionIntensity)
{
    color intensity{1, 1, 1};
    Point position{0, 0, 0};

    PointLight light{intensity, position};

    EXPECT_EQ(light.intensity, intensity);
    EXPECT_EQ(light.position, position);
}

TEST(Materials, DefaultMaterial)
{
    Material m{};

    EXPECT_EQ(m.color, color(1, 1, 1));
    EXPECT_TRUE(Math::Equal(m.ambient, 0.1f));
    EXPECT_TRUE(Math::Equal(m.diffuse, 0.9));
    EXPECT_TRUE(Math::Equal(m.specular, 0.9f));
    EXPECT_TRUE(Math::Equal(m.shininess, 200.0f));
}

TEST(Materials, SphereDefaultMaterial)
{
    Sphere s{};
    EXPECT_EQ(s.get_material(), Material());
}

TEST(Materials, AssignMaterialToSphere)
{
    Sphere s{};
    Material m{};
    m.ambient = 1;
    s.set_material(m);

    EXPECT_EQ(s.get_material(), m);
}

TEST(Lighting, EyeBetweenLightAndSurface)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 0, -10)};
    sphere_ptr sphere (new Sphere());
    color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, color(1.9, 1.9, 1.9));
}

TEST(Lighting, EyeBetweenLightAndSurfaceOffset45)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 0, -10)};
    sphere_ptr sphere (new Sphere());
    color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, color(1.0, 1.0, 1.0));
}

TEST(Lighting, EyeOppositeSurfaceOffset45)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 10, -10)};
    sphere_ptr sphere (new Sphere());
    color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, color(0.7364, 0.7364, 0.7364));
}

TEST(Lighting, EyeInPathOfReflectionVector)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(-std::sqrt(2)/2), static_cast<float>(-std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 10, -10)};
    sphere_ptr sphere (new Sphere());
    color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, color(1.6364, 1.6364, 1.6364));
}

TEST(Lighting, LightBehindSurface)
{
    Material m{};
    Point position{0, 0, -1};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 0, 10)};
    sphere_ptr sphere (new Sphere());
    color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, color(0.1, 0.1, 0.1));
}

TEST(Lighting, SurfaceInShadow)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{color(1, 1, 1), Point(0, 0, -10)};
    bool in_shadow = true;
    sphere_ptr sphere (new Sphere());

    color result = Lighting(m, sphere, light, position, eye_v, normal_v, in_shadow);

    EXPECT_EQ(result, color(0.1, 0.1, 0.1));
}

TEST(Lighting, HitShouldOffsetPoint)
{
    ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    sphere_ptr shape (new Sphere());
    shape->set_transform(Math::Translation(0, 0, 1));
    intersection i{5, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(comps.over_point.z < -std::numeric_limits<float>::epsilon()/2);
    EXPECT_TRUE(comps.point.z > comps.over_point.z);
}

TEST(Lighting, LightingWithPatternApplied)
{
    Material m{};
    std::shared_ptr<Pattern> pattern (new CStripePattern(colors::white, colors::black));
    m.SetPattern(pattern);
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{colors::white, Point(0, 0, -10)};
    sphere_ptr sphere (new Sphere());
    sphere->set_material(m);

    color c1 = Lighting(m, sphere, light, Point(0.9, 0, 0), eye_v, normal_v, false);
    color c2 = Lighting(m, sphere, light, Point(1.1, 0, 0), eye_v, normal_v, false);

    EXPECT_EQ(c1, colors::white);
    EXPECT_EQ(c2, colors::black);
}