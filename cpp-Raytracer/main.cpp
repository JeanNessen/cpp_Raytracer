#include "Canvas.h"
//#include "Sphere.h"
#include "World.h"
#include <random>

double GetRandomDouble(double min, double max)
{
    std::random_device dev;
    std::uniform_real_distribution<double> distribution(min, max);
    std::mt19937 generator(dev());
    double a = distribution(generator);
    return a;
}

bool CheckSpot(Point spot, const std::vector<Point>& taken_spots)
{
    double max_distance = 0.8;
    bool spot_is_free = true;
    for(Point s: taken_spots)
    {
        double taken_x = s.x;
        double taken_z = s.z;

        if(spot.x < taken_x + max_distance && spot.x > taken_x -max_distance && spot.z < taken_z + max_distance && spot.z > taken_z -max_distance)
        {
            spot_is_free = false;
            break;
        }
    }
    return spot_is_free;
}

int main()
{
    //Initialize the World
    World w{};
    w.SetRecursionDepth(2);

    std::cout << w.GetRecursionDepth() << std::endl;

    //Initialize the light
    PointLight default_light{color::white, Point(-5, 10, -5)};
    w.AddLight(default_light);


    //Set up the pattern for the floor
    std::shared_ptr<Pattern> p(new CheckersPattern(Color(0.8, 0.8, 0.8), Color(0.4, 0.4, 0.4)));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    Plane_ptr floor (new Plane());
    floor->GetMaterial().SetPattern(p);
    floor->GetMaterial().color = Color(1, 0.9, 0.9);
    floor->GetMaterial().specular = 0.6f;
    floor->GetMaterial().reflective = 0.05f;
    w.AddObject(floor);

    std::vector<Point> taken_spots;

    for (int i = 0; i < 50; ++i) {
        Sphere_ptr sphere(new Sphere());
        sphere->GetMaterial().color = Color(GetRandomDouble(0, 1), GetRandomDouble(0, 1), GetRandomDouble(0, 1));
        sphere->GetMaterial().diffuse = 0.7f;
        sphere->GetMaterial().specular = 0.2f;
        sphere->GetMaterial().reflective = 0.15f;
        sphere->GetMaterial().shininess = 150;
        double sphere_scaling_s = GetRandomDouble(0.25, 0.5);
        Matrix4 scaling = Math::Scaling(sphere_scaling_s);
        Point spot{GetRandomDouble(-5, 5), 0.5, GetRandomDouble(-5, 20)};
        while(!CheckSpot(spot, taken_spots))
        {
            spot = Point{GetRandomDouble(-4, 4), sphere_scaling_s, GetRandomDouble(-2, 20)};
        }
        taken_spots.push_back(spot);
        sphere->SetTransform(Math::Translation(spot.x, spot.y, spot.z) * scaling);
        w.AddObject(sphere);
    }


//    //Set up the spheres
//    Sphere_ptr sphere_01(new Sphere());
//    sphere_01->GetMaterial().color = Color(1, 0, 0);
//    sphere_01->GetMaterial().diffuse = 0.7f;
//    sphere_01->GetMaterial().specular = 0.2f;
//    sphere_01->GetMaterial().reflective = 0.15f;
//    sphere_01->GetMaterial().shininess = 150;
//    sphere_01->SetTransform(Math::Translation(-5, 1, 10));
//    w.AddObject(sphere_01);
//
//
//    Sphere_ptr sphere_02{new Sphere()};
//    sphere_02->GetMaterial().color = Color(0, 1, 0);
//    sphere_02->GetMaterial().diffuse = 0.7f;
//    sphere_02->GetMaterial().specular = 0.2f;
//    sphere_02->GetMaterial().reflective = 0.15f;
//    sphere_02->SetTransform(Math::Translation(-3, 0.25, 5) * Math::Scaling(0.25, 0.25, 0.25));
//    w.AddObject(sphere_02);
//
//
//    Sphere_ptr sphere_03(new Sphere());
//    sphere_03->GetMaterial().color = Color(0, 0, 1);
//    sphere_03->GetMaterial().diffuse = 0.7f;
//    sphere_03->GetMaterial().specular = 0.2f;
//    sphere_03->GetMaterial().reflective = 0.15f;
//    sphere_03->SetTransform(Math::Translation(0, 1, 0));
//    w.AddObject(sphere_03);
//
//    Sphere_ptr sphere_04(new Sphere());
//    sphere_04->GetMaterial().color = Color(0, 1, 1);
//    sphere_04->GetMaterial().diffuse = 0.7f;
//    sphere_04->GetMaterial().specular = 0.2f;
//    sphere_04->GetMaterial().reflective = 0.15f;
//    sphere_04->SetTransform(Math::Translation(2, 1, 5));
//    w.AddObject(sphere_04);


    //Initialize the Camera
    Camera c{100, 100, 3*(M_PI/4)};

    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(0, 3, -5), Point(0, 1, 1), Vector(0, 1, 0)));

    c.SetSamplesPerPixel(5);
    c.depth_of_field = true;
    c.anti_aliasing = true;
    c.SetApertureSize(0.08);
    c.SetFocalLength(8);

    //RenderMultiThread the image
    Canvas image = w.RenderSingleThread(c);

    image.to_ppm();



}

