//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/CRay.h"
#include "../cpp-Raytracer/CRay.cpp"

#include "../cpp-Raytracer/SIntersection.h"
#include "../cpp-Raytracer/SIntersection.cpp"

//#include "../cpp-Raytracer/SIntersectionComputations.h"
#include "../cpp-Raytracer/SIntersectionComputations.cpp"

#include "../cpp-Raytracer/CShape.h"
//#include "../cpp-Raytracer/CShape.cpp"

#include "../cpp-Raytracer/CSphere.h"
#include "../cpp-Raytracer/CSphere.cpp"

#include "../cpp-Raytracer/CColor.h"

#include "../cpp-Raytracer/Light.h"
#include "../cpp-Raytracer/Light.cpp"

#include "../cpp-Raytracer/CMaterial.h"
#include "../cpp-Raytracer/CMaterial.cpp"

#include "../cpp-Raytracer/CPattern.h"
#include "../cpp-Raytracer/CPattern.cpp"

#include <limits>

TEST(RayTracing, CreatingARay)
{
    Point origin{ 1, 2, 3 };
    Vector direction{ 4, 5, 6 };
    CRay r{origin, direction };

    EXPECT_TRUE(Math::Equal(origin, r.origin));
    EXPECT_TRUE(Math::Equal(direction, r.direction));
}

TEST(RayTracing, ComputingPointFromDistance)
{
    CRay r{Point{2, 3, 4}, Vector{1, 0, 0} };

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
    CSphere s1{};
    CSphere s2{};

    EXPECT_EQ(s1, s1);
    EXPECT_NE(s1, s2);
}

TEST(RayTracing, ComparingIntersections)
{
    Sphere_ptr s1 (new CSphere());
    Sphere_ptr s2 (new CSphere());

    SIntersection i1{1.0f, s1 };
    SIntersection i2{1.0f, s2 };
    SIntersection i3{2.0f, s1 };
    SIntersection i4{2.0f, s2 };

    EXPECT_EQ(i1, i1);
    EXPECT_NE(i1, i2);
    EXPECT_NE(i1, i3);
    EXPECT_NE(i1, i4);
}

TEST(RayTracing, RaySphereIntersection2Points)
{
    CRay r{Point{0, 0, -5}, Vector{0, 0, 1} };
    Sphere_ptr s (new CSphere());

    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 6.0f));
}

TEST(RayTracing, RayIntersectsSphereTangent)
{
    CRay r{Point(0, 1, -5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, 5.0));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.0));
}

TEST(RayTracing, RayMissesSphere)
{
    CRay r{Point(0, 2, -5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 0));
}

TEST(RayTracing, RayOriginInSphere)
{
    CRay r{Point(0, 0, 0), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -1.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 1.0f));
}

TEST(RayTracing, RayOriginBehindSphere)
{
    CRay r{Point(0, 0, 5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(xs[0].t, -6.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, -4.0f));
}

TEST(RayTracing, IntersectionEncapsulatesAnObject)
{
    Sphere_ptr s (new CSphere());
    SIntersection I1{1.0f, s };
    SIntersection I2{2.0f, s };

    std::vector<SIntersection> xs{I1, I2 };

    EXPECT_TRUE(Math::Equal(xs.size(), 2));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
}

TEST(RayTracing, Aggregating5Intersections)
{
    Sphere_ptr s1 (new CSphere());
    Sphere_ptr s2 (new CSphere());
    Sphere_ptr s3 (new CSphere());
    SIntersection I1{1.0f, s1 };
    SIntersection I2{2.0f, s1 };
    SIntersection I3{3.0f, s2 };
    SIntersection I4{4.0f, s2 };
    SIntersection I5{5.0f, s3 };

    std::vector<SIntersection> xs{I1, I2, I3, I4, I5 };

    EXPECT_TRUE(Math::Equal(xs.size(), 5));
    EXPECT_TRUE(Math::Equal(I1.t, 1.0f));
    EXPECT_TRUE(Math::Equal(I2.t, 2.0f));
    EXPECT_TRUE(Math::Equal(I3.t, 3.0f));
    EXPECT_TRUE(Math::Equal(I4.t, 4.0f));
    EXPECT_TRUE(Math::Equal(I5.t, 5.0f));
}

TEST(RayTracing, IntersectSetsTheObjectOnTheIntersection)
{
    CRay r{Point(0, 0, 5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(xs[0].object, s);
    EXPECT_EQ(xs[1].object, s);
}

TEST(RayTracing, HitWhenAllIntersectionsHavePositiveT)
{
    Sphere_ptr s (new CSphere());
    SIntersection i1{1, s };
    SIntersection i2{2, s };
    std::vector<SIntersection> xs{i2, i1 };

    SIntersection *i = Hit(xs);

    EXPECT_EQ(*i, i1);
}

TEST(RayTracing, HitWhenSomeIntersectionsHaveNegativeT)
{
    Sphere_ptr s(new CSphere());
    SIntersection i1{-1, s };
    SIntersection i2{1, s };
    std::vector<SIntersection> xs{i2, i1 };

    SIntersection *i = Hit(xs);

    EXPECT_EQ(*i, i2);
}

TEST(RayTracing, HitWhenAllIntersectionsAreNegative)
{
    Sphere_ptr s (new CSphere());
    SIntersection i1{-1, s };
    SIntersection i2{-2, s };
    std::vector<SIntersection> xs{i2, i1 };

    SIntersection *i = Hit(xs);

    EXPECT_EQ(i, nullptr);
}

TEST(RayTracing, HitIsAlwaysLowestNotNegativeIntersection)
{
    Sphere_ptr s (new CSphere());
    SIntersection i1{5, s };
    SIntersection i2{7, s };
    SIntersection i3{-3, s };
    SIntersection i4{2, s };

    std::vector<SIntersection> xs{i1, i2, i3, i4 };

    SIntersection *i = Hit(xs);

    EXPECT_EQ(*i, i4);
}

TEST(RayTracing, TranslatingARay)
{
    CRay r{Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Translation(3, 4, 5);

    CRay r2 = r.Transform(m);

    EXPECT_EQ(r2.origin, Point(4, 6, 8));
    EXPECT_EQ(r2.direction, Vector(0, 1, 0));
}

TEST(RayTracing, ScalingARay)
{
    CRay r{Point(1, 2, 3), Vector(0, 1, 0) };
    Matrix4 m = Math::Scaling(2, 3, 4);

    CRay r2 = r.Transform(m);

    EXPECT_EQ(r2.origin, Point(2, 6, 12));
    EXPECT_EQ(r2.direction, Vector(0, 3, 0));
}

TEST(RayTracing, SphereDefaultTransformation)
{
    CSphere s{};

    EXPECT_EQ(s.GetTransform(), Math::identiy_matrix);
}

TEST(RayTracing, ChangingSphereTransform)
{
    CSphere s{};
    Matrix4 t = Math::Translation(2, 3, 4);

    s.SetTransform(t);

    EXPECT_EQ(s.GetTransform(), t);
}

TEST(RayTracing, IntersectingScaledSphereWithRay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    s->SetTransform(Math::Scaling(2, 2, 2));
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 3.0f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 7.0f));
}

TEST(RayTracing, IntersectingScaledSphereWithRay2)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    s->SetTransform(Math::Scaling(0.5, 0.5, 0.5));
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.5f));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5.5f));
}

TEST(RayTracing, IntersectingTranslatedSphereWithRay)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1) };
    Sphere_ptr s (new CSphere());

    s->SetTransform(Math::Translation(5, 0, 0));
    std::vector<SIntersection> xs = r.Intersect(s);

    EXPECT_EQ(xs.size(), 0);
}

TEST(RayTracing, NormalOnSphereX)
{
    Sphere_ptr s (new CSphere());
    Vector n = s->NormalAt(Point(1, 0, 0));

    EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(RayTracing, NormalOnSphereY)
{
    Sphere_ptr s (new CSphere());
    Vector n = s->NormalAt(Point(0, 1, 0));

    EXPECT_EQ(n, Vector(0, 1, 0));
}

TEST(RayTracing, NormalOnSphereZ)
{
    Sphere_ptr s (new CSphere());
    Vector n = s->NormalAt(Point(0, 0, 1));

    EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(RayTracing, NormalNonaxial)
{
    Sphere_ptr s (new CSphere());
    Vector n = s->NormalAt(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, Vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));
}

TEST(RayTracing, NormalVectorIsNormalized)
{
    Sphere_ptr s (new CSphere());
    Vector n = s->NormalAt(Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    EXPECT_EQ(n, n.normalized());
}

TEST(RayTracing, NormalOnTranslatedSphere)
{
    Sphere_ptr s (new CSphere());
    s->SetTransform(Math::Translation(0, 1, 0));
    Vector n = s->NormalAt(Point(0, 1.70711, -0.70711));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.70711, -0.70711)));
}

TEST(RayTracing, NormalOnTransformedSphere)
{
    CSphere s{};
    Matrix4 m = Math::Scaling(1, 0.5, 1) * Math::Rotation_Z(M_PI/5);

    s.SetTransform(m);
    Vector n = s.NormalAt(Point(0, std::sqrt(2)/2, -std::sqrt(2)/2));

    EXPECT_TRUE(Math::Equal(n, Vector(0, 0.97014, -0.24254)));
}

TEST(RayTracing, PrecomputingStateOfAnIntersection)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere_ptr shape (new CSphere());
    SIntersection i{4, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.t, i.t);
    EXPECT_EQ(comps.object, i.object);
    EXPECT_EQ(comps.point, Point(0, 0, -1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1));
}

TEST(RayTracing, HitWhenIntersectionOccursOnOutside)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere_ptr shape (new CSphere());
    SIntersection i{4, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_FALSE(comps.inside);
}

TEST(RayTracing, HitWhenIntersectionOccursOnInside)
{
    CRay r{Point(0, 0, 0), Vector(0, 0, 1)};
    Sphere_ptr shape (new CSphere());
    SIntersection i{1, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_EQ(comps.point, Point(0, 0, 1));
    EXPECT_EQ(comps.eye_v, Vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normal_v, Vector(0, 0, -1)); //inverted because the hit occured on the inside
}

TEST(Lighting, PointLightPositionIntensity)
{
    CColor intensity{1, 1, 1};
    Point position{0, 0, 0};

    SPointLight light{intensity, position};

    EXPECT_EQ(light.intensity, intensity);
    EXPECT_EQ(light.position, position);
}

TEST(Materials, DefaultMaterial)
{
    CMaterial m{};

    EXPECT_EQ(m.color, CColor(1, 1, 1));
    EXPECT_TRUE(Math::Equal(m.ambient, 0.1f));
    EXPECT_TRUE(Math::Equal(m.diffuse, 0.9));
    EXPECT_TRUE(Math::Equal(m.specular, 0.9f));
    EXPECT_TRUE(Math::Equal(m.shininess, 200.0f));
}

TEST(Materials, SphereDefaultMaterial)
{
    CSphere s{};
    EXPECT_EQ(s.GetMaterial(), CMaterial());
}

TEST(Materials, AssignMaterialToSphere)
{
    CSphere s{};
    CMaterial m{};
    m.ambient = 1;
    s.SetMaterial(m);

    EXPECT_EQ(s.GetMaterial(), m);
}

TEST(Lighting, EyeBetweenLightAndSurface)
{
    CMaterial m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 0, -10)};
    Sphere_ptr sphere (new CSphere());
    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, CColor(1.9, 1.9, 1.9));
}

TEST(Lighting, EyeBetweenLightAndSurfaceOffset45)
{
    CMaterial m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 0, -10)};
    Sphere_ptr sphere (new CSphere());
    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, CColor(1.0, 1.0, 1.0));
}

TEST(Lighting, EyeOppositeSurfaceOffset45)
{
    CMaterial m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 10, -10)};
    Sphere_ptr sphere (new CSphere());
    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, CColor(0.7364, 0.7364, 0.7364));
}

TEST(Lighting, EyeInPathOfReflectionVector)
{
    CMaterial m{};
    Point position{0, 0, 0};

    Vector eye_v{0, static_cast<float>(-std::sqrt(2)/2), static_cast<float>(-std::sqrt(2)/2)};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 10, -10)};
    Sphere_ptr sphere (new CSphere());
    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, CColor(1.6364, 1.6364, 1.6364));
}

TEST(Lighting, LightBehindSurface)
{
    CMaterial m{};
    Point position{0, 0, -1};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 0, 10)};
    Sphere_ptr sphere (new CSphere());
    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, false);

    EXPECT_EQ(result, CColor(0.1, 0.1, 0.1));
}

TEST(Lighting, SurfaceInShadow)
{
    CMaterial m{};
    Point position{0, 0, 0};

    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    SPointLight light{CColor(1, 1, 1), Point(0, 0, -10)};
    bool in_shadow = true;
    Sphere_ptr sphere (new CSphere());

    CColor result = Lighting(m, sphere, light, position, eye_v, normal_v, in_shadow);

    EXPECT_EQ(result, CColor(0.1, 0.1, 0.1));
}

TEST(Lighting, HitShouldOffsetPoint)
{
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    Sphere_ptr shape (new CSphere());
    shape->SetTransform(Math::Translation(0, 0, 1));
    SIntersection i{5, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);

    EXPECT_TRUE(comps.over_point.z < -std::numeric_limits<float>::epsilon()/2);
    EXPECT_TRUE(comps.point.z > comps.over_point.z);
}

TEST(Lighting, LightingWithPatternApplied)
{
    CMaterial m{};
    std::shared_ptr<CPattern> pattern (new CStripePattern(color::white, color::black));
    m.SetPattern(pattern);
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    Vector eye_v{0, 0, -1};
    Vector normal_v{0, 0, -1};
    SPointLight light{color::white, Point(0, 0, -10)};
    Sphere_ptr sphere (new CSphere());
    sphere->SetMaterial(m);

    CColor c1 = Lighting(m, sphere, light, Point(0.9, 0, 0), eye_v, normal_v, false);
    CColor c2 = Lighting(m, sphere, light, Point(1.1, 0, 0), eye_v, normal_v, false);

    EXPECT_EQ(c1, color::white);
    EXPECT_EQ(c2, color::black);
}