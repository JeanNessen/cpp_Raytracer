#include "Canvas.h"
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

void PlaceSpheres(World w)
{
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
}

int main()
{
    //Initialize the World
    World w{};
    w.SetRecursionDepth(5);

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

    Sphere_ptr blue_sphere{new Sphere()};
    blue_sphere->GetMaterial().color = color::blue;
    blue_sphere->SetTransform(Math::Translation(0.5, 1, 3) * Math::Scaling(0.25));
    w.AddObject(blue_sphere);


    Sphere_ptr glass_sphere{new Sphere()};
    glass_sphere->GetMaterial().color = color::black;
    glass_sphere->GetMaterial().transparency = 1;
    glass_sphere->GetMaterial().refractive_index = 2;
    glass_sphere->GetMaterial().reflective = 1;
    glass_sphere->GetMaterial().diffuse = 0.25;
    glass_sphere->GetMaterial().ambient = 0.25;
    glass_sphere->GetMaterial().specular = 1;
    glass_sphere->GetMaterial().shininess = 300;
    glass_sphere->SetTransform(Math::Translation(0, 1, 1));
    w.AddObject(glass_sphere);

    //Initialize the Camera

    Camera c{1000, 1000, 3*(M_PI/4)};


    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(0.5543, 3.0865, -5), Point(0, 1, 1), Vector(0, 1, 0)));

    c.SetSamplesPerPixel(1);
    c.depth_of_field = false;
    c.anti_aliasing = false;
    c.SetApertureSize(0.08);
    c.SetFocalLength(8);

    //RenderMultiThread the image
    Canvas image = w.RenderSingleThread(c);

    image.to_ppm();



}

