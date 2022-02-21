#include "Tracer.h"
#include "Color.h"
#include "Canvas.h"
#include <iostream>
#include <string>
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
#include "Light.h"
#include "World.h"
#include "Intersection.h"


int main()
{
    //Initialize the World
    World w = DefaultWorld();

    w.GetWorldObjects().clear();

    //Set up the floor
    Sphere floor{};
    floor.SetTransform(Math::Scaling(10, 0.01, 10));
    floor.GetMaterial().color = Color(1, 0.9, 0.9);
    floor.GetMaterial().specular = 0.0f;
    w.AddObject(floor);


    //Set up the right wall
    Sphere right_wall{};
    right_wall.SetTransform(Math::Translation(0, 0, 5) *
                            Math::Rotation_Y(M_PI / 4) * Math::Rotation_X(M_PI / 2) *
                            Math::Scaling(10, 0.01, 10));
    right_wall.SetMaterial(floor.GetMaterial());
    w.AddObject(right_wall);


    //Set up the left wall
    Sphere left_wall{};
    left_wall.SetTransform( Math::Translation(0, 0, 5) *
                            Math::Rotation_Y(-M_PI /4) * Math::Rotation_X(M_PI/ 2) *
                            Math::Scaling(10, 0.01, 10));
    left_wall.SetMaterial(floor.GetMaterial());
    w.AddObject(right_wall);
    w.AddObject(left_wall);

    //Set up the spheres
    Sphere sphere_01{};
    sphere_01.GetMaterial().color = Color(1, 0, 0);
    sphere_01.GetMaterial().diffuse = 0.7f;
    sphere_01.GetMaterial().specular = 0.2f;
    sphere_01.SetTransform(Math::Translation(-3, 1, 2));
    w.AddObject(sphere_01);


    Sphere sphere_02{};
    sphere_02.GetMaterial().color = Color(0, 1, 0);
    sphere_02.GetMaterial().diffuse = 0.7f;
    sphere_02.GetMaterial().specular = 0.2f;
    sphere_02.SetTransform(Math::Translation(1, 2, 0) * Math::Scaling(2, 2, 2));
    w.AddObject(sphere_02);


    Sphere sphere_03{};
    sphere_03.GetMaterial().color = Color(0, 0, 1);
    sphere_03.GetMaterial().diffuse = 0.7f;
    sphere_03.GetMaterial().specular = 0.2f;
    sphere_03.SetTransform(Math::Translation(0, 1, 2));
    w.AddObject(sphere_03);


    //Initialize the Camera
    Camera c{250, 250, M_PI/2};

    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

    //Render the image
    Canvas image = w.Render(c);

    image.to_ppm();

}