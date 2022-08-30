//
// Created by Jean-Luc von Nessen on 25.02.22.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Material.h"

#include "../cpp-Raytracer/Shapes/Plane.h"
#include "../cpp-Raytracer/IntersectionComputations.h"
#include "../cpp-Raytracer/World.h"

TEST(Reflections, ReflectivityForDefaultMaterial)
{
    material m{};

    EXPECT_EQ(m.reflective, 0);
}

TEST(Reflections, PrecomputingReflectionVector)
{
    plane_ptr p (new plane());
    ray r{point(0, 1, -1), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    intersection i{sqrt(2), p};

    intersection_computations comps = PrepareComputations(i, r);

    EXPECT_TRUE(Math::Equal(comps.reflect_v, vector(0, sqrt(2)/2, sqrt(2)/2)));
}

TEST(Reflections, ReflectedColorForNonreflectiveMaterial)
{
    World w = DefaultWorld();
    ray r{point(0, 0, 0), vector(0, 0, 1)};
    sphere_ptr shape = dynamic_pointer_cast<Sphere>(w.get_world_objects()[1]);
    shape->get_material().ambient = 1;
    intersection i{1, shape};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.calculate_reflected_color(comps);

    EXPECT_EQ(c, color(0, 0, 0));
}

TEST(Reflections, ReflectedColorForReflectiveMaterial)
{
    World w = DefaultWorld();
    plane_ptr shape (new plane());
    shape->get_material().reflective = 0.5;
    shape->set_transform(Math::Translation(0, -1, 0));
    w.add_object(shape);
    ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    intersection i{sqrt(2), shape};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.calculate_reflected_color(comps);

    EXPECT_EQ(c, color(0.19032, 0.2379, 0.14274));
}

TEST(Reflections, ShadeHitWithReflectiveMaterial)
{
    World w = DefaultWorld();
    plane_ptr shape (new plane());
    shape->get_material().reflective = 0.5;
    shape->set_transform(Math::Translation(0, -1, 0));
    w.add_object(shape);
    ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    intersection i{sqrt(2), shape};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.shade_hit(comps);

    EXPECT_EQ(c, color(0.87677, 0.92436, 0.82918));
}

TEST(Reflections, ColorAtWithMutuallyReflectiveSurfaces)
{
    World w{};
    w.add_light(point_light(colors::white, point(0, 0, 0)));

    plane_ptr lower(new plane());
    lower->get_material().reflective = 1;
    lower->set_transform(Math::Translation(0, -1, 0));
    w.add_object(lower);

    plane_ptr upper(new plane());
    upper->get_material().reflective = 1;
    upper->set_transform(Math::Translation(0, 1, 0));
    w.add_object(upper);

    ray r{point(0, 0, 0), vector(0, 1, 0)};

    color c = w.calculate_color_at(r);
}

TEST(Reflections, TheReflectedColorAtMaximumRecursiveDepth)
{
    World w = DefaultWorld();
    plane_ptr p(new plane());
    p->get_material().reflective = 0.5;
    p->set_transform(Math::Translation(0, -1, 0));
    w.add_object(p);
    ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    intersection i{sqrt(2), p};

    intersection_computations comps = PrepareComputations(i, r);
    color c = w.calculate_reflected_color(comps, 0);

    EXPECT_EQ(c, colors::black);

}