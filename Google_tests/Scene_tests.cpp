//
// Created by Jean-Luc von Nessen on 24.01.22.
//


#include <algorithm>

#include "gtest/gtest.h"

#include "../cpp-Raytracer/World.h"
#include "../cpp-Raytracer/World.cpp"

#include "../cpp-Raytracer/Camera.h"
#include "../cpp-Raytracer/Camera.cpp"

#include "../cpp-Raytracer/Canvas.h"

#include "../cpp-Raytracer/Intersection.h"
//#include "../cpp-Raytracer/Intersection.cpp"

#include "../cpp-Raytracer/IntersectionComputations.h"
//#include "../cpp-Raytracer/IntersectionComputations.cpp"

TEST(World, WorldCreation)
{
    World w{};

    EXPECT_TRUE(w.GetWorldLights().empty());
    EXPECT_TRUE(w.GetWorldObjects().empty());
}

TEST(World, DefaultWorld)
{
    PointLight light{Color(1, 1, 1), Point(-10, 10, -10)};

    Sphere sphere_1{};
    sphere_1.GetMaterial().color = Color{0.8, 1.0, 0.6};
    sphere_1.GetMaterial().diffuse = 0.7;
    sphere_1.GetMaterial().specular = 0.2;

    Sphere sphere_2{};
    sphere_2.SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    World w = DefaultWorld();

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
    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

    std::vector<Intersection> xs = w.IntersectWorld(r);

    EXPECT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}

TEST(World, ShadingAnIntersection)
{
    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
    auto shape = w.GetWorldObjects()[0];
    Intersection i{4, shape};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.ShadeHit(comps);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(World, ShadingAnIntersectionFromInside)
{
    World w = DefaultWorld();
    w.GetWorldLights()[0] = PointLight{Color(1, 1, 1), Point(0, 0.25, 0)};
    Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.GetWorldObjects()[1];
    Intersection i{0.5, shape};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.ShadeHit(comps);
    EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(World, ColorWhenRayMisses)
{
    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 1, 0)};

    Color c = w.ColorAt(r);

    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(World, ColorWhenRayHits)
{
    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

    Color c = w.ColorAt(r);

    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(World, ColorWithIntersectionBehinRay)
{
    World w = DefaultWorld();
    auto outer = w.GetWorldObjects()[0];
    outer->GetMaterial().ambient = 1;
    auto inner = w.GetWorldObjects()[1];
    inner->GetMaterial().ambient = 1;
    Ray r{Point(0, 0, 0.75), Vector(0, 0, -1)};

    Color c = w.ColorAt(r);

    EXPECT_EQ(c, inner->GetMaterial().color);
}

TEST(Camera, ConstructingACamera)
{
    int h_size{160};
    int v_size{120};
    float fov{M_PI / 2};

    Camera c{h_size, v_size, fov};

    EXPECT_EQ(c.GetHSize(), 160);
    EXPECT_EQ(c.GetVSize(), 120);
    EXPECT_TRUE(Math::Equal(c.GetFOV(), M_PI/2));
    EXPECT_EQ(c.GetTransform(), Math::identiy_matrix);
}

TEST(Camera, PixelSizeHorizontalCanvas)
{
    Camera c{200, 125, M_PI/2};

    EXPECT_TRUE(Math::Equal(c.GetPixelSize(), 0.01));
}

TEST(Camera, PixelSizeVerticalCanvas)
{
    Camera c{125, 200, M_PI/2};

    EXPECT_TRUE(Math::Equal(c.GetPixelSize(), 0.01));
}

TEST(Camera, ConstructingRayThroughCenterOfCanvas)
{
    Camera c{201, 101, M_PI/2};

    Ray r = c.RayForPixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0, 0, -1)));
}

TEST(Camera, ConstructingRayThroughCorneOfCanvas)
{
    Camera c{201, 101, M_PI/2};

    Ray r = c.RayForPixel(0, 0);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0.66519, 0.33259, -0.66851)));
}

TEST(Camera, ConsturctingRayWhenCameraIsTransformed)
{
    Camera c{201, 101, M_PI/2};

    c.SetTransform(Math::Rotation_Y(M_PI/4) * Math::Translation(0, -2, 5));
    Ray r = c.RayForPixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, Point(0, 2, -5)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(std::sqrt(2)/2, 0, -sqrt(2)/2)));
}

TEST(Camera, RenderingAWorldWithACamera)
{
    World w = DefaultWorld();
    Camera c{11, 11, M_PI/2};
    Point from{0, 0, -5};
    Point to{0, 0, 0};
    Vector up{0, 1, 0};
    c.SetTransform(Math::ViewTransform(from, to, up));

    Canvas image = w.Render(c);

    EXPECT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}

TEST(World, NoShadowWhenNothingIsCollinearWithPointAndLight)
{
    World w = DefaultWorld();
    Point p{0, 10, 0};

    EXPECT_FALSE(w.IsShadowed(p));
}

TEST(World, ShadowWhenObjectIsBetweenPointAndLight)
{
    World w = DefaultWorld();
    Point p{10, -10, 10};

    EXPECT_TRUE(w.IsShadowed(p));
}

TEST(World, NoShadowWhenObjectIsBehindLight)
{
    World w = DefaultWorld();
    Point p{-20, 20, -20};

    EXPECT_FALSE(w.IsShadowed(p));
}

TEST(World, NoShadowWhenObjectIsBehindPoint)
{
    World w = DefaultWorld();
    Point p{-2, 2,-2};

    EXPECT_FALSE(w.IsShadowed(p));
}

TEST(Lighting, ShadeHitIsGivenIntersectionInShadow)
{
    World w{};
    w.AddLight(PointLight{Color(1, 1, 1), Point(0, 0, -10)});

    //Add the first sphere
    Sphere_ptr s1 (new Sphere());
    w.AddObject(s1);

    //Add the second sphere
    Sphere_ptr s2 (new Sphere());
    s2->SetTransform(Math::Translation(0, 0, 10));
    w.AddObject(s2);

    Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
    Intersection i{4, s2};

    IntersectionComputations comps = PrepareComputations(i, r);
    Color c = w.ShadeHit(comps);

    EXPECT_EQ(c, Color(0.1, 0.1, 0.1));
}