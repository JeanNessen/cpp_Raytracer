//
// Created by Jean-Luc von Nessen on 24.01.22.
//


#include <algorithm>

#include "gtest/gtest.h"

#include "../cpp-Raytracer/CWorld.h"
#include "../cpp-Raytracer/CWorld.cpp"

#include "../cpp-Raytracer/CCamera.h"
#include "../cpp-Raytracer/CCamera.cpp"

#include "../cpp-Raytracer/CCanvas.h"

#include "../cpp-Raytracer/SIntersection.h"
//#include "../cpp-Raytracer/SIntersection.cpp"

#include "../cpp-Raytracer/SIntersectionComputations.h"
//#include "../cpp-Raytracer/SIntersectionComputations.cpp"

TEST(World, WorldCreation)
{
    CWorld w{};

    EXPECT_TRUE(w.GetWorldLights().empty());
    EXPECT_TRUE(w.GetWorldObjects().empty());
}

TEST(World, DefaultWorld)
{
    SPointLight light{CColor(1, 1, 1), Point(-10, 10, -10)};

    CSphere sphere_1{};
    sphere_1.GetMaterial().color = CColor{0.8, 1.0, 0.6};
    sphere_1.GetMaterial().diffuse = 0.7;
    sphere_1.GetMaterial().specular = 0.2;

    CSphere sphere_2{};
    sphere_2.SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    CWorld w = DefaultWorld();

    //Check if the default world contains the correct light
    auto default_light_it = std::find(w.GetWorldLights().begin(), w.GetWorldLights().end(), light);
    EXPECT_NE(default_light_it, w.GetWorldLights().end());

/*    //Check if the default world contains the correct spheres
    auto default_sphere_1_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_1);
    EXPECT_NE(default_sphere_1_it, w.GetWorldObjects().end());

    auto default_sphere_2_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_2);
    EXPECT_NE(default_sphere_2_it, w.GetWorldObjects().end());*/

    EXPECT_EQ(w.GetWorldObjects()[0]->GetMaterial(), sphere_1.GetMaterial());
    EXPECT_EQ(w.GetWorldObjects()[0]->GetTransform(), sphere_1.GetTransform());

    EXPECT_EQ(w.GetWorldObjects()[1]->GetMaterial(), sphere_2.GetMaterial());
    EXPECT_EQ(w.GetWorldObjects()[1]->GetTransform(), sphere_2.GetTransform());
}

TEST(World, IntersectWorldWithRay)
{
    CWorld w = DefaultWorld();
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};

    std::vector<SIntersection> xs = w.IntersectWorld(r);

    EXPECT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}

TEST(World, ShadingAnIntersection)
{
    CWorld w = DefaultWorld();
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto shape = w.GetWorldObjects()[0];
    SIntersection i{4, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.ShadeHit(comps);

    EXPECT_EQ(c, CColor(0.38066, 0.47583, 0.2855));
}

TEST(World, ShadingAnIntersectionFromInside)
{
    CWorld w = DefaultWorld();
    w.GetWorldLights()[0] = SPointLight{CColor(1, 1, 1), Point(0, 0.25, 0)};
    CRay r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.GetWorldObjects()[1];
    SIntersection i{0.5, shape};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.ShadeHit(comps);
    EXPECT_EQ(c, CColor(0.90498, 0.90498, 0.90498));
}

TEST(World, ColorWhenRayMisses)
{
    CWorld w = DefaultWorld();
    CRay r{Point(0, 0, -5), Vector(0, 1, 0)};

    CColor c = w.CalculateColorAt(r);

    EXPECT_EQ(c, CColor(0, 0, 0));
}

TEST(World, ColorWhenRayHits)
{
    CWorld w = DefaultWorld();
    CRay r{Point(0, 0, -5), Vector(0, 0, 1)};

    CColor c = w.CalculateColorAt(r);

    EXPECT_EQ(c, CColor(0.38066, 0.47583, 0.2855));
}

TEST(World, ColorWithIntersectionBehinRay)
{
    CWorld w = DefaultWorld();
    auto outer = w.GetWorldObjects()[0];
    outer->GetMaterial().ambient = 1;
    auto inner = w.GetWorldObjects()[1];
    inner->GetMaterial().ambient = 1;
    CRay r{Point(0, 0, 0.75), Vector(0, 0, -1)};

    CColor c = w.CalculateColorAt(r);

    EXPECT_EQ(c, inner->GetMaterial().color);
}

TEST(Camera, ConstructingACamera)
{
    int h_size{160};
    int v_size{120};
    float fov{M_PI / 2};

    CCamera c{h_size, v_size, fov};

    EXPECT_EQ(c.GetHSize(), 160);
    EXPECT_EQ(c.GetVSize(), 120);
    EXPECT_TRUE(Math::Equal(c.GetFOV(), M_PI/2));
    EXPECT_EQ(c.GetTransform(), Math::identiy_matrix);
}

TEST(Camera, PixelSizeHorizontalCanvas)
{
    CCamera c{200, 125, M_PI / 2};

    EXPECT_TRUE(Math::Equal(c.GetPixelSize(), 0.01));
}

TEST(Camera, PixelSizeVerticalCanvas)
{
    CCamera c{125, 200, M_PI / 2};

    EXPECT_TRUE(Math::Equal(c.GetPixelSize(), 0.01));
}

TEST(Camera, ConstructingRayThroughCenterOfCanvas)
{
    CCamera c{201, 101, M_PI / 2};

    CRay r = c.RayForPixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0, 0, -1)));
}

TEST(Camera, ConstructingRayThroughCorneOfCanvas)
{
    CCamera c{201, 101, M_PI / 2};
    c.SetFocalLength(1);

    CRay r = c.RayForPixel(0, 0);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0.66519, 0.33259, -0.66851)));
}

TEST(Camera, ConsturctingRayWhenCameraIsTransformed)
{
    CCamera c{201, 101, M_PI / 2};

    c.SetTransform(Math::Rotation_Y(M_PI/4) * Math::Translation(0, -2, 5));
    CRay r = c.RayForPixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 2, -5)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(std::sqrt(2)/2, 0, -sqrt(2)/2)));
}

TEST(Camera, RenderingAWorldWithACamera)
{
    CWorld w = DefaultWorld();
    CCamera c{11, 11, M_PI / 2};
    Point from{0, 0, -5};
    Point to{0, 0, 0};
    Vector up{0, 1, 0};
    c.SetTransform(Math::ViewTransform(from, to, up));

    CCanvas image = w.RenderSingleThread(c);

    EXPECT_EQ(image.PixelAt(5, 5), CColor(0.38066, 0.47583, 0.2855));
}

TEST(World, NoShadowWhenNothingIsCollinearWithPointAndLight)
{
    CWorld w = DefaultWorld();
    Point p{0, 10, 0};

    EXPECT_FALSE(w.CalculateShadow(p));
}

TEST(World, ShadowWhenObjectIsBetweenPointAndLight)
{
    CWorld w = DefaultWorld();
    Point p{10, -10, 10};

    EXPECT_TRUE(w.CalculateShadow(p));
}

TEST(World, NoShadowWhenObjectIsBehindLight)
{
    CWorld w = DefaultWorld();
    Point p{-20, 20, -20};

    EXPECT_FALSE(w.CalculateShadow(p));
}

TEST(World, NoShadowWhenObjectIsBehindPoint)
{
    CWorld w = DefaultWorld();
    Point p{-2, 2,-2};

    EXPECT_FALSE(w.CalculateShadow(p));
}

TEST(Lighting, ShadeHitIsGivenIntersectionInShadow)
{
    CWorld w{};
    w.AddLight(SPointLight{CColor(1, 1, 1), Point(0, 0, -10)});

    //Add the first sphere
    Sphere_ptr s1 (new CSphere());
    w.AddObject(s1);

    //Add the second sphere
    Sphere_ptr s2 (new CSphere());
    s2->SetTransform(Math::Translation(0, 0, 10));
    w.AddObject(s2);

    CRay r{Point(0, 0, 5), Vector(0, 0, 1)};
    SIntersection i{4, s2};

    SIntersectionComputations comps = PrepareComputations(i, r);
    CColor c = w.ShadeHit(comps);

    EXPECT_EQ(c, CColor(0.1, 0.1, 0.1));
}