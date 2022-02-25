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

#include "../cpp-Raytracer/Shape.h"
//#include "../cpp-Raytracer/Shape.cpp"

#include "../cpp-Raytracer/Sphere.h"
#include "../cpp-Raytracer/Sphere.cpp"

#include "../cpp-Raytracer/Color.h"

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
    Sphere s1{};
    Sphere s2{};

    EXPECT_EQ(s1, s1);
    EXPECT_NE(s1, s2);
}

TEST(RayTracing, ComparingIntersections)
{
    std::shared_ptr<Sphere> s1 (new Sphere());
    std::shared_ptr<Sphere> s2 (new Sphere());

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
    std::shared_ptr<Sphere> s (new Sphere());

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 6.0f));
}

TEST(RayTracing, RayIntersectsSphereTangent)
{
    Ray r{ Point(0, 1, -5), Vector(0, 0, 1) };
    std::shared_ptr<Sphere> s (new Sphere());

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 5.0));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.0));
}

TEST(RayTracing, RayMissesSphere)
{
    Ray r{ Point(0, 2, -5), Vector(0, 0, 1) };
    std::shared_ptr<Sphere> s (new Sphere());

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 0));
}

TEST(RayTracing, RayOriginInSphere)
{
    Ray r{ Point(0, 0, 0), Vector(0, 0, 1) };
    std::shared_ptr<Sphere> s (new Sphere());

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -1.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 1.0f));
}

TEST(RayTracing, RayOriginBehindSphere)
{
    Ray r{ Point(0, 0, 5), Vector(0, 0, 1) };
    std::shared_ptr<Sphere> s (new Sphere());

    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -6.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, -4.0f));
}

TEST(RayTracing, IntersectionEncapsulatesAnObject)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Intersection I1{ 1.0f, s };
    Intersection I2{ 2.0f, s };

    std::vector<Intersection> xs = Intersections({ I1, I2 });

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
}

TEST(RayTracing, Aggregating5Intersections)
{
    std::shared_ptr<Sphere> s1 (new Sphere());
    std::shared_ptr<Sphere> s2 (new Sphere());
    std::shared_ptr<Sphere> s3 (new Sphere());
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
    std::shared_ptr<Sphere> s (new Sphere());
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs[0].object, s);
    EXPECT_EQ(xs[1].object, s);
}

TEST(RayTracing, HitWhenAllIntersectionsHavePositiveT)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Intersection i1{ 1, s };
    Intersection i2{ 2, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(*i, i1);
}

TEST(RayTracing, HitWhenSomeIntersectionsHaveNegativeT)
{
    std::shared_ptr<Sphere> s(new Sphere());
    Intersection i1{ -1, s };
    Intersection i2{ 1, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(*i, i2);
}

TEST(RayTracing, HitWhenAllIntersectionsAreNegative)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Intersection i1{ -1, s };
    Intersection i2{ -2, s };
    std::vector<Intersection> xs{ i2, i1 };

    Intersection *i = Hit(xs);

    EXPECT_EQ(i, nullptr);
}

TEST(RayTracing, HitIsAlwaysLowestNotNegativeIntersection)
{
    std::shared_ptr<Sphere> s (new Sphere());
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
    Sphere s{};

    EXPECT_EQ(s.GetTransform(), Math::identiy_matrix);
}

TEST(RayTracing, ChangingSphereTransform)
{
    Sphere s{};
    Matrix4 t = Math::Translation(2, 3, 4);

    s.SetTransform(t);

    EXPECT_EQ(s.GetTransform(), t);
}

TEST(RayTracing, IntersectingScaledSphereWithRay)
{
    Ray r{ Point(0,0,-5), Vector(0,0,1) };
    std::shared_ptr<Sphere> s (new Sphere());

    s->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 3.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 7.0f));
}

TEST(RayTracing, IntersectingScaledSphereWithRay2)
{
    Ray r{ Point(0,0,-5), Vector(0,0,1) };
    std::shared_ptr<Sphere> s (new Sphere());

    s->SetTransform(Math::Scaling(0.5, 0.5, 0.5));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.5f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.5f));
}

TEST(RayTracing, IntersectingTranslatedSphereWithRay)
{
    Ray r{ Point(0,0,-5), Vector(0,0,1) };
    std::shared_ptr<Sphere> s (new Sphere());

    s->SetTransform(Math::Translation(5, 0, 0));
    std::vector<Intersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 0);
}

TEST(RayTracing, NormalOnSphereX)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Vector n = s->NormalAt(Point(1, 0, 0));

    EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(RayTracing, NormalOnSphereY)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Vector n = s->NormalAt(Point(0, 1, 0));

    EXPECT_EQ(n, Vector(0, 1, 0));
}

TEST(RayTracing, NormalOnSphereZ)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Vector n = s->NormalAt(Point(0, 0, 1));

    EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(RayTracing, NormalNonaxial)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Vector n = s->NormalAt(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, Vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));
}

TEST(RayTracing, NormalVectorIsNormalized)
{
    std::shared_ptr<Sphere> s (new Sphere());
    Vector n = s->NormalAt(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, n.normalized());
}

TEST(RayTracing, NormalOnTranslatedSphere)
{
    std::shared_ptr<Sphere> s (new Sphere());
    s->SetTransform(Math::Translation(0, 1, 0));
    Vector n = s->NormalAt(Point(0, 1.70711, -0.70711));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.70711, -0.70711)));
}

TEST(RayTracing, NormalOnTransformedSphere)
{
    Sphere s{};
    Matrix4 m = Math::Scaling(1, 0.5, 1) * Math::Rotation_Z(M_PI/5);

    s.SetTransform(m);
    Vector n = s.NormalAt(Point(0, std::sqrt(2)/2, -std::sqrt(2)/2));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.97014, -0.24254)));
}

TEST(RayTracing, PrecomputingStateOfAnIntersection)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Sphere> shape (new Sphere());
    Intersection i{4, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, Point(0, 0, -1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1));
}

TEST(RayTracing, HitWhenIntersectionOccursOnOutside)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Sphere> shape (new Sphere());
    Intersection i{4, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_FALSE(comps.inside);
}

TEST(RayTracing, HitWhenIntersectionOccursOnInside)
{
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    std::shared_ptr<Sphere> shape (new Sphere());
    Intersection i{1, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.point, Point(0, 0, 1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1)); //inverted because the hit occured on the inside
}

TEST(Lighting, PointLightPositionIntensity)
{
    Color intensity{1, 1, 1};
    Point position{0, 0, 0};

    PointLight light{intensity, position};

    EXPECT_EQ(light.intensity, intensity);
    EXPECT_EQ(light.position, position);
}

TEST(Materials, DefaultMaterial)
{
    Material m{};

    EXPECT_EQ(m.color, Color(1, 1, 1));
    EXPECT_TRUE(Math::Equal(m.ambient, 0.1f));
    EXPECT_TRUE(Math::Equal(m.diffuse, 0.9));
    EXPECT_TRUE(Math::Equal(m.specular, 0.9f));
    EXPECT_TRUE(Math::Equal(m.shininess, 200.0f));
}

TEST(Materials, SphereDefaultMaterial)
{
    Sphere s{};
    EXPECT_EQ(s.GetMaterial(), Material());
}

TEST(Materials, AssignMaterialToSphere)
{
    Sphere s{};
    Material m{};
    m.ambient = 1;
    s.SetMaterial(m);

    EXPECT_EQ(s.GetMaterial(), m);
}

TEST(Lighting, EyeBetweenLightAndSurface)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0, 0, -10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(Lighting, EyeBetweenLightAndSurfaceOffset45)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0,0, -10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(Lighting, EyeOppositeSurfaceOffset45)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0,10, -10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(Lighting, EyeInPathOfReflectionVector)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(-std::sqrt(2)/2), static_cast<float>(-std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0,10, -10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(Lighting, LightBehindSurface)
{
    Material m{};
    Point position{0, 0, -1};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0,0, 10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(Lighting, SurfaceInShadow)
{
    Material m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point(0, 0, -10)};
    bool in_shadow = true;
    std::shared_ptr<Sphere> sphere (new Sphere());

    Color result = Lighting(m, sphere, light, position, eye_v, normal_v, in_shadow);

    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(Lighting, HitShouldOffsetPoint)
{
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    std::shared_ptr<Sphere> shape (new Sphere());
    shape->SetTransform(Math::Translation(0, 0, 1));
    Intersection i{5, shape};

    IntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(comps.over_point.z < -std::numeric_limits<float>::epsilon()/2);
    EXPECT_TRUE(comps.point.z > comps.over_point.z);
}

TEST(Lighting, LightingWithPatternApplied)
{
    Material m{};
    std::shared_ptr<Pattern> pattern (new StripePattern(color::white, color::black));
    m.SetPattern(pattern);
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    PointLight light{color::white, Point(0, 0, -10)};
    std::shared_ptr<Sphere> sphere (new Sphere());
    sphere->SetMaterial(m);

    Color c1 = Lighting(m, sphere, light, Point(0.9, 0, 0), eye_v, normal_v, false);
    Color c2 = Lighting(m, sphere, light, Point(1.1, 0, 0), eye_v, normal_v, false);

    EXPECT_EQ(c1, color::white);
    EXPECT_EQ(c2, color::black);
}