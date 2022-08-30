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

    EXPECT_TRUE(w.get_world_lights().empty());
    EXPECT_TRUE(w.get_world_objects().empty());
}

TEST(World, DefaultWorld)
{
    point_light light{color(1, 1, 1), point(-10, 10, -10)};

    Sphere sphere_1{};
    sphere_1.get_material().color = color{0.8, 1.0, 0.6};
    sphere_1.get_material().diffuse = 0.7;
    sphere_1.get_material().specular = 0.2;

    Sphere sphere_2{};
    sphere_2.set_transform(Math::Scaling(0.5, 0.5, 0.5));

    World w = DefaultWorld();

    //Check if the default world contains the correct light
    auto default_light_it = std::find(w.get_world_lights().begin(), w.get_world_lights().end(), light);
    EXPECT_NE(default_light_it, w.get_world_lights().end());

/*    //Check if the default world contains the correct spheres
    auto default_sphere_1_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_1);
    EXPECT_NE(default_sphere_1_it, w.GetWorldObjects().end());

    auto default_sphere_2_it = std::find(w.GetWorldObjects().begin(), w.GetWorldObjects().end(), sphere_2);
    EXPECT_NE(default_sphere_2_it, w.GetWorldObjects().end());*/

    EXPECT_EQ(w.get_world_objects()[0]->get_material(), sphere_1.get_material());
    EXPECT_EQ(w.get_world_objects()[0]->get_transform(), sphere_1.get_transform());

    EXPECT_EQ(w.get_world_objects()[1]->get_material(), sphere_2.get_material());
    EXPECT_EQ(w.get_world_objects()[1]->get_transform(), sphere_2.get_transform());
}

TEST(World, IntersectWorldWithRay)
{
    World w = DefaultWorld();
    ray r{point(0, 0, -5), Vector(0, 0, 1)};

    std::vector<intersection> xs = w.intersect_world(r);

    EXPECT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 4.5);
    EXPECT_EQ(xs[2].t, 5.5);
    EXPECT_EQ(xs[3].t, 6);
}

TEST(World, ShadingAnIntersection)
{
    World w = DefaultWorld();
    ray r{point(0, 0, -5), Vector(0, 0, 1)};
    auto shape = w.get_world_objects()[0];
    intersection i{4, shape};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.shade_hit(comps);

    EXPECT_EQ(c, color(0.38066, 0.47583, 0.2855));
}

TEST(World, ShadingAnIntersectionFromInside)
{
    World w = DefaultWorld();
    w.get_world_lights()[0] = point_light{color(1, 1, 1), point(0, 0.25, 0)};
    ray r{point(0, 0, 0), Vector(0, 0, 1)};
    auto shape = w.get_world_objects()[1];
    intersection i{0.5, shape};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.shade_hit(comps);
    EXPECT_EQ(c, color(0.90498, 0.90498, 0.90498));
}

TEST(World, ColorWhenRayMisses)
{
    World w = DefaultWorld();
    ray r{point(0, 0, -5), Vector(0, 1, 0)};

    color c = w.calculate_color_at(r);

    EXPECT_EQ(c, color(0, 0, 0));
}

TEST(World, ColorWhenRayHits)
{
    World w = DefaultWorld();
    ray r{point(0, 0, -5), Vector(0, 0, 1)};

    color c = w.calculate_color_at(r);

    EXPECT_EQ(c, color(0.38066, 0.47583, 0.2855));
}

TEST(World, ColorWithIntersectionBehinRay)
{
    World w = DefaultWorld();
    auto outer = w.get_world_objects()[0];
    outer->get_material().ambient = 1;
    auto inner = w.get_world_objects()[1];
    inner->get_material().ambient = 1;
    ray r{point(0, 0, 0.75), Vector(0, 0, -1)};

    color c = w.calculate_color_at(r);

    EXPECT_EQ(c, inner->get_material().color);
}

TEST(Camera, ConstructingACamera)
{
    int h_size{160};
    int v_size{120};
    double fov{M_PI / 2};

    camera c{h_size, v_size, fov};

    EXPECT_EQ(c.get_h_size(), 160);
    EXPECT_EQ(c.get_v_size(), 120);
    EXPECT_TRUE(Math::Equal(c.get_fov(), M_PI/2));
    EXPECT_EQ(c.get_transform(), Math::identiy_matrix);
}

TEST(Camera, PixelSizeHorizontalCanvas)
{
    camera c{200, 125, M_PI / 2};

    EXPECT_TRUE(Math::Equal(c.get_pixel_size(), 0.01));
}

TEST(Camera, PixelSizeVerticalCanvas)
{
    camera c{125, 200, M_PI / 2};

    EXPECT_TRUE(Math::Equal(c.get_pixel_size(), 0.01));
}

TEST(Camera, ConstructingRayThroughCenterOfCanvas)
{
    camera c{201, 101, M_PI / 2};

    ray r = c.ray_for_pixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0, 0, -1)));
}

TEST(Camera, ConstructingRayThroughCorneOfCanvas)
{
    camera c{201, 101, M_PI / 2};
    c.set_focal_length(1);

    ray r = c.ray_for_pixel(0, 0);

    EXPECT_TRUE(Math::Equal(r.origin, point(0, 0, 0)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(0.66519, 0.33259, -0.66851)));
}

TEST(Camera, ConsturctingRayWhenCameraIsTransformed)
{
    camera c{201, 101, M_PI / 2};

    c.set_transform(Math::Rotation_Y(M_PI/4) * Math::Translation(0, -2, 5));
    ray r = c.ray_for_pixel(100, 50);

    EXPECT_TRUE(Math::Equal(r.origin, point(0, 2, -5)));
    EXPECT_TRUE(Math::Equal(r.direction, Vector(std::sqrt(2)/2, 0, -sqrt(2)/2)));
}

TEST(Camera, RenderingAWorldWithACamera)
{
    World w = DefaultWorld();
    camera c{11, 11, M_PI / 2};
    point from{0, 0, -5};
    point to{0, 0, 0};
    Vector up{0, 1, 0};
    c.set_transform(Math::ViewTransform(from, to, up));

    canvas image = w.render_multi_thread(c, 1);

    EXPECT_EQ(image.pixel_at(5, 5), color(0.38066, 0.47583, 0.2855));
}

TEST(World, NoShadowWhenNothingIsCollinearWithPointAndLight)
{
    World w = DefaultWorld();
    point p{0, 10, 0};

    EXPECT_FALSE(w.calculate_shadow(p));
}

TEST(World, ShadowWhenObjectIsBetweenPointAndLight)
{
    World w = DefaultWorld();
    point p{10, -10, 10};

    EXPECT_TRUE(w.calculate_shadow(p));
}

TEST(World, NoShadowWhenObjectIsBehindLight)
{
    World w = DefaultWorld();
    point p{-20, 20, -20};

    EXPECT_FALSE(w.calculate_shadow(p));
}

TEST(World, NoShadowWhenObjectIsBehindPoint)
{
    World w = DefaultWorld();
    point p{-2, 2,-2};

    EXPECT_FALSE(w.calculate_shadow(p));
}

TEST(Lighting, ShadeHitIsGivenIntersectionInShadow)
{
    World w{};
    w.add_light(point_light{color(1, 1, 1), point(0, 0, -10)});

    //Add the first sphere
    sphere_ptr s1 (new Sphere());
    w.add_object(s1);

    //Add the second sphere
    sphere_ptr s2 (new Sphere());
    s2->set_transform(Math::Translation(0, 0, 10));
    w.add_object(s2);

    ray r{point(0, 0, 5), Vector(0, 0, 1)};
    intersection i{4, s2};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.shade_hit(comps);

    EXPECT_EQ(c, color(0.1, 0.1, 0.1));
}