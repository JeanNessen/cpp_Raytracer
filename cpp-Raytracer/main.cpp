#include "Canvas.h"
//#include "Sphere.h"
#include "World.h"


int main()
{
    //Initialize the World
    World w{};

    //Initialize the light
    PointLight default_light{Color(1, 1, 1), Point(-10, 10, -10)};
    w.AddLight(default_light);


    //Set up the pattern for the floor
    std::shared_ptr<Pattern> p(new CheckersPattern(color::white, color::black));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    Plane_ptr floor (new Plane());
    floor->GetMaterial().SetPattern(p);
    floor->GetMaterial().color = Color(1, 0.9, 0.9);
    floor->GetMaterial().specular = 0.6f;
    floor->GetMaterial().reflective = 0.1f;
    w.AddObject(floor);


    //Set up the right wall
    Sphere_ptr right_wall( new Sphere());
    right_wall->SetTransform(Math::Translation(0, 0, 5) *
                            Math::Rotation_Y(M_PI / 4) * Math::Rotation_X(M_PI / 2) *
                            Math::Scaling(10, 0.01, 10));
    right_wall->SetMaterial(floor->GetMaterial());
    //w.AddObject(right_wall);


    //Set up the left wall
    Sphere_ptr left_wall(new Sphere());
    left_wall->SetTransform( Math::Translation(0, 0, 5) *
                            Math::Rotation_Y(-M_PI /4) * Math::Rotation_X(M_PI/ 2) *
                            Math::Scaling(10, 0.01, 10));
    left_wall->SetMaterial(floor->GetMaterial());
    //w.AddObject(left_wall);

    //Set up the spheres
    Sphere_ptr sphere_01(new Sphere());
    sphere_01->GetMaterial().color = Color(1, 0, 0);
    sphere_01->GetMaterial().diffuse = 0.7f;
    sphere_01->GetMaterial().specular = 0.2f;
    sphere_01->GetMaterial().reflective = 0.7f;
    sphere_01->SetTransform(Math::Translation(-1, 1, -2));
    w.AddObject(sphere_01);


    Sphere_ptr sphere_02{new Sphere()};
    sphere_02->GetMaterial().color = Color(0, 1, 0);
    sphere_02->GetMaterial().diffuse = 0.7f;
    sphere_02->GetMaterial().specular = 0.2f;
    sphere_02->GetMaterial().reflective = 0.6f;
    sphere_02->SetTransform(Math::Translation(1.5, 0.5, -1) * Math::Scaling(0.25, 0.25, 0.25));
    w.AddObject(sphere_02);


    Sphere_ptr sphere_03(new Sphere());
    sphere_03->GetMaterial().color = Color(0, 0, 1);
    sphere_03->GetMaterial().diffuse = 0.7f;
    sphere_03->GetMaterial().specular = 0.2f;
    sphere_03->GetMaterial().reflective = 0.5f;
    sphere_03->SetTransform(Math::Translation(0, 1, 1));
    w.AddObject(sphere_03);


    //Initialize the Camera
    Camera c{1920, 1080, M_PI/2};

    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

    //Render the image
    Canvas image = w.Render(c);

    image.to_ppm();



}