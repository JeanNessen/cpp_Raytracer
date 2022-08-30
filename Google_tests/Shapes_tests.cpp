//
// Created by Jean-Luc von Nessen on 21.02.22.
//



#include "gtest/gtest.h"

#include "../cpp-Raytracer/Shapes/shape.h"
#include "../cpp-Raytracer/Shapes/shape.cpp"

#include "../cpp-Raytracer/Shapes/Sphere.h"
//#include "../cpp-Raytracer/Sphere.cpp"

#include "../cpp-Raytracer/Intersection.h"

#include "../cpp-Raytracer/Shapes/Plane.h"
#include "../cpp-Raytracer/Shapes/Plane.cpp"

#include "../cpp-Raytracer/Ray.h"

#include "../cpp-Raytracer/Shapes/Cube.cpp"

#include "../cpp-Raytracer/Shapes/Cylinder.h"
#include "../cpp-Raytracer/Shapes/Cylinder.cpp"

#include"../cpp-Raytracer/Shapes/Cone.h"
#include"../cpp-Raytracer/Shapes/Cone.cpp"


#include <vector>

TEST(Spheres, TheDefaultTransformation)
{
    Sphere s{};

    EXPECT_EQ(s.get_transform(), Math::identiy_matrix);
}

TEST(Spheres, AssigningATransformation)
{
    Sphere s{};

    s.set_transform(Math::Translation(2, 3, 4));

    EXPECT_EQ(s.get_transform(), Math::Translation(2, 3, 4));
}

TEST(Spheres, TheDefaultMaterial)
{
    Sphere s{};

    EXPECT_EQ(s.get_material(), material{});
}

TEST(Spheres, AssigningAMaterial)
{
    Sphere s{};
    material m{};
    m.ambient = 1;

    s.set_material(m);

    EXPECT_EQ(s.get_material(), m);
}

TEST(Spheres, IntersectingAScaledSphereWithARay)
{
    ray r{point(0, 0, -5), Vector(0, 0, 1)};
    sphere_ptr s (new Sphere());

    s->set_transform(Math::Scaling(2, 2, 2));
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(s->saved_ray_origin, point(0, 0, -2.5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Spheres, IntersectingATranslatedSphereWithARay)
{
    ray r{point(0, 0, -5), Vector(0, 0, 1)};
    sphere_ptr s(new Sphere());

    s->set_transform(Math::Translation(5, 0, 0));
    std::vector<intersection> xs = r.intersect(s);

    EXPECT_EQ(s->saved_ray_origin, point(-5, 0, -5));
    EXPECT_EQ(s->saved_ray_direction, Vector(0, 0, 1));
}

TEST(Planes, TheDefaultTransformation)
{
    plane p{};

    EXPECT_EQ(p.get_transform(), Math::identiy_matrix);
}

TEST(Planes, AssigningATransformation)
{
    plane p{};

    p.set_transform(Math::Translation(2, 3, 4));

    EXPECT_EQ(p.get_transform(), Math::Translation(2, 3, 4));
}

TEST(Planes, TheDefaultMaterial)
{
    plane p{};

    EXPECT_EQ(p.get_material(), material{});
}

TEST(Planes, AssigningAMaterial)
{
    plane p{};
    material m{};
    m.ambient = 1;

    p.set_material(m);

    EXPECT_EQ(p.get_material(), m);
}

TEST(Planes, IntersectingAScaledPlaneWithARay)
{
    ray r{point(0, 0, -5), Vector(0, 0, 1)};
    plane_ptr p (new plane());

    p->set_transform(Math::Scaling(2, 2, 2));
    std::vector<intersection> xs = r.intersect(p);

    EXPECT_EQ(p->saved_ray_origin, point(0, 0, -2.5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 0.5));
}

TEST(Planes, IntersectingATranslatedPlaneWithARay)
{
    ray r{point(0, 0, -5), Vector(0, 0, 1)};
    plane_ptr p (new plane());

    p->set_transform(Math::Translation(5, 0, 0));
    std::vector<intersection> xs = r.intersect(p);

    EXPECT_EQ(p->saved_ray_origin, point(-5, 0, -5));
    EXPECT_EQ(p->saved_ray_direction, Vector(0, 0, 1));
}

TEST(Planes, TheNormalOfAPlaneIsConstantEverywhere)
{
    plane p{};

    Vector n1 = p.local_normal_at(point(0, 0, 0));
    Vector n2 = p.local_normal_at(point(10, 0, -10));
    Vector n3 = p.local_normal_at(point(-5, 0, 150));

    Vector n = Vector(0, 1, 0);

    EXPECT_EQ(n1, n);
    EXPECT_EQ(n2, n);
    EXPECT_EQ(n3, n);
}

TEST(Planes, IntersectWithARayParallelToThePlane)
{
    plane_ptr p (new plane());
    ray r{point(0, 10, 10), Vector(0, 0, 1)};

    std::vector<intersection> xs = r.local_intersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, IntersectWithACoplanarRay)
{
    plane_ptr p (new plane());
    ray r{point(0, 0, 0), Vector(0, 0, 1)};

    std::vector<intersection> xs = r.local_intersect(p);

    EXPECT_TRUE(xs.empty());
}

TEST(Planes, ARayIntersectingAPlaneFormAbove)
{
    plane_ptr p (new plane());
    ray r{point(0, 1, 0), Vector(0, -1, 0)};

    std::vector<intersection> xs = r.local_intersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}

TEST(Planes, ARayIntersectingAPlaneFormBelow)
{
    plane_ptr p (new plane());
    ray r{point(0, -1, 0), Vector(0, 1, 0)};

    std::vector<intersection> xs = r.local_intersect(p);

    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, p);
}

TEST(Cubes, RayIntersectsCube_01)
{
    cube_ptr c (new cube());
    ray r{point(5, 0.5, 0), Vector(-1, 0, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_02)
{
    cube_ptr c (new cube());
    ray r{point(-5, 0.5, 0), Vector(1, 0, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_03)
{
    cube_ptr c (new cube());
    ray r{point(0.5, 5, 0), Vector(0, -1, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_04)
{
    cube_ptr c (new cube());
    ray r{point(0.5, -5, 0), Vector(0, 1, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_05)
{
    cube_ptr c (new cube());
    ray r{point(0.5, 0, 5), Vector(0, 0, -1)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_06)
{
    cube_ptr c (new cube());
    ray r{point(0.5, 0, -5), Vector(0, 0, 1)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cubes, RayIntersectsCube_07)
{
    cube_ptr c (new cube());
    ray r{point(0, 0.5, 0), Vector(0, 0, 1)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, -1);
    EXPECT_EQ(xs[1].t, 1);
}

TEST(Cubes, RayMissesCube_01)
{
    cube_ptr c (new cube());
    ray r{point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_02)
{
    cube_ptr c (new cube());
    ray r{point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_03)
{
    cube_ptr c (new cube());
    ray r{point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_04)
{
    cube_ptr c (new cube());
    ray r{point(2, 0, 2), Vector(0, 0, -1)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_05)
{
    cube_ptr c (new cube());
    ray r{point(0, 2, 2), Vector(0, -1, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, RayMissesCube_06)
{
    cube_ptr c (new cube());
    ray r{point(2, 2, 0), Vector(-1, 0, 0)};

    std::vector<intersection> xs = r.local_intersect(c);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cubes, NormalOnCubeSurface_01)
{
    cube_ptr c (new cube());
    point p{1, 0.5, -0.8};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_02)
{
    cube_ptr c (new cube());
    point p{-1, -0.2, 0.9};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(-1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_03)
{
    cube_ptr c (new cube());
    point p{-0.4, 1, -0.1};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(0, 1, 0));
}

TEST(Cubes, NormalOnCubeSurface_04)
{
    cube_ptr c (new cube());
    point p{0.3, -1, -0.7};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(0, -1, 0));
}

TEST(Cubes, NormalOnCubeSurface_05)
{
    cube_ptr c (new cube());
    point p{-0.6, 0.3, 1};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(0, 0, 1));
}

TEST(Cubes, NormalOnCubeSurface_06)
{
    cube_ptr c (new cube());
    point p{0.4, 0.4, -1};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(0, 0, -1));
}

TEST(Cubes, NormalOnCubeSurface_07)
{
    cube_ptr c (new cube());
    point p{1, 1, 1};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(1, 0, 0));
}

TEST(Cubes, NormalOnCubeSurface_08)
{
    cube_ptr c (new cube());
    point p{-1, -1, -1};
    Vector normal = c->local_normal_at(p);

    EXPECT_EQ(normal, Vector(-1, 0, 0));
}

TEST(Cylinders, RayMissesCylinder_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 0, 1, 0 };
    direction = direction.normalized();

    ray r{ point{1, 0, 0}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, RayMissesCylinder_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 0, 1, 0 };
    direction = direction.normalized();

    ray r{ point{0, 0, 0}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, RayMissesCylinder_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 1, 1, 1 };
    direction = direction.normalized();

    ray r{ point{0, 0, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, RayIntersectsCylinder_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{1, 0, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 5);
    EXPECT_EQ(xs[1].t, 5);
}

TEST(Cylinders, RayIntersectsCylinder_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 0, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4);
    EXPECT_EQ(xs[1].t, 6);
}

TEST(Cylinders, RayIntersectsCylinder_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector direction{ 0.1, 1, 1 };
    direction = direction.normalized();

    ray r{ point{0.5, 0, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 6.80798));
    EXPECT_TRUE(Math::Equal(xs[1].t, 7.08872));
}

TEST(Cylinders, NormalOnCylinderSurface_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector n = cyl->local_normal_at(point{ 1, 0, 0 });

    EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(Cylinders, NormalOnCylinderSurface_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector n = cyl->local_normal_at(point{ 0, 5, -1 });

    EXPECT_EQ(n, Vector(0, 0, -1));
}

TEST(Cylinders, NormalOnCylinderSurface_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector n = cyl->local_normal_at(point{ 0, -2, 1 });

    EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(Cylinders, NormalOnCylinderSurface_04)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    Vector n = cyl->local_normal_at(point{ -1, 1, 0 });

    EXPECT_EQ(n, Vector(-1, 0, 0));
}

TEST(Cylinders, DefaultMinAndMaxForCylinder)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    EXPECT_EQ(cyl->minimum, -std::numeric_limits<double>::infinity());
    EXPECT_EQ(cyl->maximum, std::numeric_limits<double>::infinity());

}

TEST(Cylinders, IntersectingTruncatedCylinder_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0.1, 1, 0 };
    direction = direction.normalized();

    ray r{ point{0, 1.5, 0}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, IntersectingTruncatedCylinder_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 3, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, IntersectingTruncatedCylinder_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 0, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, IntersectingTruncatedCylinder_04)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 2, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, IntersectingTruncatedCylinder_05)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 1, -5}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 0);
}

TEST(Cylinders, IntersectingTruncatedCylinder_06)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 1.5, -2}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, DefaultClosedValueForCylinder)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };

    EXPECT_FALSE(cyl->closed);
}

TEST(Cylinders, IntersectingCapsOfClosedCylinder_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, -1, 0 };
    direction = direction.normalized();

    ray r{ point{0, 3, 0}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, IntersectingCapsOfClosedCylinder_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, -1, 2 };
    direction = direction.normalized();

    ray r{ point{0, 3, -2}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, IntersectingCapsOfClosedCylinder_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, -1, 1 };
    direction = direction.normalized();

    ray r{ point{0, 4, -2}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, IntersectingCapsOfClosedCylinder_04)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 1, 2 };
    direction = direction.normalized();

    ray r{ point{0, 0, -2}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, IntersectingCapsOfClosedCylinder_05)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector direction{ 0, 1, 1 };
    direction = direction.normalized();

    ray r{ point{0, -1, -2}, direction };

    std::vector<intersection> xs = r.local_intersect(cyl);

    EXPECT_EQ(xs.size(), 2);
}

TEST(Cylinders, NormalOnCylinderCaps_01)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0, 1, 0}) };

    EXPECT_EQ(normal, Vector(0, -1, 0));
}

TEST(Cylinders, NormalOnCylinderCaps_02)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0.5, 1, 0}) };

    EXPECT_EQ(normal, Vector(0, -1, 0));
}

TEST(Cylinders, NormalOnCylinderCaps_03)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0, 1, 0.5}) };

    EXPECT_EQ(normal, Vector(0, -1, 0));
}

TEST(Cylinders, NormalOnCylinderCaps_04)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0, 2, 0}) };

    EXPECT_EQ(normal, Vector(0, 1, 0));
}

TEST(Cylinders, NormalOnCylinderCaps_05)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0.5, 2, 0}) };

    EXPECT_EQ(normal, Vector(0, 1, 0));
}

TEST(Cylinders, NormalOnCylinderCaps_06)
{
    cylinder_ptr cyl{ std::make_shared<cylinder>(cylinder{}) };
    cyl->closed = true;

    cyl->minimum = 1;
    cyl->maximum = 2;

    Vector normal{ cyl->local_normal_at({0, 2, 0.5}) };

    EXPECT_EQ(normal, Vector(0, 1, 0));
}

TEST(Cones, IntersectingConeWithRay_01)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector direction{ 0, 0, 1 };
    direction = direction.normalized();

    ray r{ point{0, 0, -5}, direction };

    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 5));
    EXPECT_TRUE(Math::Equal(xs[1].t, 5));
}

TEST(Cones, IntersectingConeWithRay_02)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector direction{ 1, 1, 1 };
    direction = direction.normalized();

    ray r{ point{0, 0, -5}, direction };

    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 8.66025));
    EXPECT_TRUE(Math::Equal(xs[1].t, 8.66025));
}

TEST(Cones, IntersectingConeWithRay_03)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector direction{ -0.5, -1, 1 };
    direction = direction.normalized();

    ray r{ point{1, 1, -5}, direction };

    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 2);
    EXPECT_TRUE(Math::Equal(xs[0].t, 4.55006));
    EXPECT_TRUE(Math::Equal(xs[1].t, 49.44994));
}

TEST(Cones, IntersectingConeWithRayParalelToOneHalve)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector direction{ 0, 1, 1 };
    direction = direction.normalized();

    ray r{ {0, 0, -1}, direction };

    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 1);
    EXPECT_TRUE(Math::Equal(xs[0].t, 0.35355));
}

TEST(Cones, IntersectingConesCaps_01)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };
    c->minimum = -0.5;
    c->maximum = 0.5;
    c->closed = true;

    Vector direction{ Vector{0, 1, 0}.normalized() };
    ray r{ point{0, 0, -5}, direction };
    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 0);
}

TEST(Cones, IntersectingConesCaps_02)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };
    c->minimum = -0.5;
    c->maximum = 0.5;
    c->closed = true;

    Vector direction{ Vector{0, 1, 1}.normalized() };
    ray r{ point{0, 0, -0.25}, direction };
    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 2);
}

TEST(Cones, IntersectingConesCaps_03)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };
    c->minimum = -0.5;
    c->maximum = 0.5;
    c->closed = true;

    Vector direction{ Vector{0, 1, 0}.normalized() };
    ray r{ point{0, 0, -0.25}, direction };
    std::vector<intersection> xs{ r.local_intersect(c) };

    ASSERT_EQ(xs.size(), 4);
}

TEST(Cones, NormalOnConeSurface_01)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector n{ c->local_normal_at(point{0, 0, 0}) };

    EXPECT_EQ(n, Vector( 0, 0, 0 ));
}

TEST(Cones, NormalOnConeSurface_02)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector n{ c->local_normal_at(point{1, 1, 1}) };

    EXPECT_EQ(n, Vector(1, -std::sqrt(2), 1));
}

TEST(Cones, NormalOnConeSurface_03)
{
    cone_ptr c{ std::make_shared<cone>(cone{}) };

    Vector n{ c->local_normal_at(point{-1, -1, 0}) };

    EXPECT_EQ(n, Vector(-1, 1, 0));
}