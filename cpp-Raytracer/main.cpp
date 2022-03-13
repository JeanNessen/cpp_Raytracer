#include "CCanvas.h"
#include "CWorld.h"
#include <random>

bool CheckSpot(Point spot, const std::vector<Point>& taken_spots)
{
    double max_distance = 0.5;
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

void PlaceSpheres(CWorld &w)
{
    std::vector<Point> taken_spots;

    for (int i = 0; i < 25; ++i) {
        Sphere_ptr sphere(new CSphere());
        sphere->GetMaterial().color = CColor(Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1));
        sphere->GetMaterial().diffuse = 0.7f;
        sphere->GetMaterial().specular = 0.2f;
        sphere->GetMaterial().reflective = 0.1;
        sphere->GetMaterial().shininess = 150;
        double sphere_scaling_s = Math::GetRandomDouble(0.1, 0.25);
        Matrix4 scaling = Math::Scaling(sphere_scaling_s);
        Point spot{Math::GetRandomDouble(-5, 5), sphere_scaling_s, Math::GetRandomDouble(10, 20)};
        while(!CheckSpot(spot, taken_spots))
        {
            spot = Point{Math::GetRandomDouble(-5, 5), sphere_scaling_s, Math::GetRandomDouble(10, 20)};
        }
        taken_spots.push_back(spot);
        sphere->SetTransform(Math::Translation(spot.x, spot.y, spot.z) * scaling);
        w.AddObject(sphere);
    }
}

int main()
{
    //Initialize the CWorld
    CWorld w{};
    w.SetRecursionDepth(5);

    //Initialize the light
    SPointLight default_light{color::white, Point(-5, 10, -5)};
    w.AddLight(default_light);


    //Set up the m_pattern for the floor
    std::shared_ptr<CPattern> p(new CCheckersPattern(CColor(0.8, 0.8, 0.8), CColor(0.4, 0.4, 0.4)));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    Plane_ptr floor (new CPlane());
    floor->GetMaterial().SetPattern(p);
    floor->GetMaterial().color = CColor(1, 0.9, 0.9);
    floor->GetMaterial().specular = 0.6f;
    floor->GetMaterial().reflective = 0.05f;
    w.AddObject(floor);

    PlaceSpheres(w);


    Sphere_ptr glass_sphere{new CSphere()};
    glass_sphere->GetMaterial().color = color::black;
    glass_sphere->GetMaterial().transparency = 1;
    glass_sphere->GetMaterial().refractive_index = 1.3;
    glass_sphere->GetMaterial().reflective = 1;
    glass_sphere->GetMaterial().diffuse = 0.25;
    glass_sphere->GetMaterial().ambient = 0.25;
    glass_sphere->GetMaterial().specular = 1;
    glass_sphere->GetMaterial().shininess = 300;
    glass_sphere->GetMaterial().throws_shadow = false;
    glass_sphere->SetTransform(Math::Translation(0, 0.75, 1) * Math::Scaling(0.75));
    w.AddObject(glass_sphere);

    //Initialize the CCamera

    CCamera c{1600, 1000, 3 * (M_PI / 4)};


    //Position the CCamera
    c.SetTransform(Math::ViewTransform(Point(0.0, 1.6865, -20), Point(0, 1, 1), Vector(0, 1, 0)));


    c.SetSamplesPerPixel(100);
    c.depth_of_field = true;
    c.anti_aliasing = true;
    c.SetApertureSize(0.1);
    c.SetFocalLength(20.3122);

    //RenderMultiThread the image
    CCanvas image = w.RenderSingleThread(c);

    image.to_ppm();



}

