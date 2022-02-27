#include "Canvas.h"
//#include "Sphere.h"
#include "World.h"


int main()
{
    //Initialize the World
    World w{};

    //Initialize the light
    PointLight default_light{color::white, Point(-5, 3, -5)};
    w.AddLight(default_light);


    //Set up the pattern for the floor
    std::shared_ptr<Pattern> p(new CheckersPattern(color::white, color::black));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    Plane_ptr floor (new Plane());
    floor->GetMaterial().SetPattern(p);
    floor->GetMaterial().color = Color(1, 0.9, 0.9);
    floor->GetMaterial().specular = 0.6f;
    floor->GetMaterial().reflective = 0.05f;
    w.AddObject(floor);


    //Set up the back wall
    Plane_ptr back_wall( new Plane());
    back_wall->SetTransform(Math::Translation(0, 0, 20) *
                                Math::Rotation_X(M_PI / 2));
    back_wall->GetMaterial().specular = 0;
    w.AddObject(back_wall);

    //Set up the wall behind the camera
    Plane_ptr cam_wall( new Plane());
    cam_wall->SetTransform(Math::Translation(0, 0, -10) *
                            Math::Rotation_X(-M_PI / 2));
    cam_wall->GetMaterial().specular = 0;
    w.AddObject(cam_wall);


    //Set up the left wall
    Plane_ptr left_wall( new Plane());
    left_wall->SetTransform(Math::Translation(10, 0, 0) *
                           Math::Rotation_Z(M_PI / 2));
    left_wall->GetMaterial().specular = 0;
    w.AddObject(left_wall);

    //Set up the right wall
    Plane_ptr right_wall( new Plane());
    right_wall->SetTransform(Math::Translation(-10, 0, 0) *
                            Math::Rotation_Z(-M_PI / 2));
    right_wall->GetMaterial().specular = 0;
    w.AddObject(right_wall);

    //Set up the spheres
    Sphere_ptr sphere_01(new Sphere());
    sphere_01->GetMaterial().color = Color(1, 0, 0);
    sphere_01->GetMaterial().diffuse = 0.7f;
    sphere_01->GetMaterial().specular = 0.2f;
    sphere_01->GetMaterial().reflective = 0.15f;
    sphere_01->GetMaterial().shininess = 150;
    sphere_01->SetTransform(Math::Translation(-5, 1, 10));
    w.AddObject(sphere_01);


    Sphere_ptr sphere_02{new Sphere()};
    sphere_02->GetMaterial().color = Color(0, 1, 0);
    sphere_02->GetMaterial().diffuse = 0.7f;
    sphere_02->GetMaterial().specular = 0.2f;
    sphere_02->GetMaterial().reflective = 0.15f;
    sphere_02->SetTransform(Math::Translation(-3, 0.25, 5) * Math::Scaling(0.25, 0.25, 0.25));
    w.AddObject(sphere_02);


    Sphere_ptr sphere_03(new Sphere());
    sphere_03->GetMaterial().color = Color(0, 0, 1);
    sphere_03->GetMaterial().diffuse = 0.7f;
    sphere_03->GetMaterial().specular = 0.2f;
    sphere_03->GetMaterial().reflective = 0.15f;
    sphere_03->SetTransform(Math::Translation(0, 1, 0));
    w.AddObject(sphere_03);

    Sphere_ptr sphere_04(new Sphere());
    sphere_04->GetMaterial().color = Color(0, 1, 1);
    sphere_04->GetMaterial().diffuse = 0.7f;
    sphere_04->GetMaterial().specular = 0.2f;
    sphere_04->GetMaterial().reflective = 0.15f;
    sphere_04->SetTransform(Math::Translation(2, 1, 5));
    w.AddObject(sphere_04);


    //Initialize the Camera
    Camera c{50, 50, 3*(M_PI/4)};

    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));

    c.SetSamplesPerPixel(500);

    //Render the image
    Canvas image = w.Render(c);

    image.to_ppm();



}