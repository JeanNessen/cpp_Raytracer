#include "Canvas.h"
#include "World.h"
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

void PlaceSpheres(World &w)
{
    std::vector<Point> taken_spots;

    for (int i = 0; i < 25; ++i) {
        Sphere_ptr sphere(new Sphere());
        sphere->GetMaterial().color = Color(Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1));
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
        w.add_object(sphere);
    }
}

int main()
{
    //Initialize the World
    World w{};
    w.set_recursion_depth(5);

    //Initialize the light
    PointLight default_light{color::white, Point(-5, 10, -5)};
    w.add_light(default_light);


    //Set up the m_pattern for the floor
    std::shared_ptr<Pattern> p(new CCheckersPattern(Color(0.8, 0.8, 0.8), Color(0.4, 0.4, 0.4)));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    Plane_ptr floor (new Plane());
    floor->GetMaterial().SetPattern(p);
    floor->GetMaterial().color = Color(1, 0.9, 0.9);
    floor->GetMaterial().specular = 0.6f;
    floor->GetMaterial().reflective = 0.05f;
    w.add_object(floor);

    //Set Glass material
    Material glass_mat{};
    glass_mat.color = color::black;
    glass_mat.transparency = 0.8;
    glass_mat.refractive_index = 1.51;
    glass_mat.reflective = 1;
    glass_mat.diffuse = 0.25;
    glass_mat.ambient = 0.25;
    glass_mat.specular = 1;
    glass_mat.shininess = 300;
    glass_mat.throws_shadow = false;


    Cube_ptr glass_cube (new Cube());
    glass_cube->SetTransform(Math::Translation(-0.6, 0.5+EPSILON, 10) * Math::Scaling(0.5));
    glass_cube->SetMaterial(glass_mat);
    w.add_object(glass_cube);

    //PlaceSpheres(w);

    Sphere_ptr glass_sphere{ std::make_shared<Sphere>(Sphere{}) };
	glass_sphere->SetTransform(Math::Translation(-1.8, 0.5 + EPSILON, 10) * Math::Scaling(0.5));
	glass_sphere->SetMaterial(glass_mat);
	w.add_object(glass_sphere);

    Cone_ptr glass_cone{ std::make_shared<Cone>(Cone{}) };
    glass_cone->SetTransform(Math::Translation(0.6, 0.5 + EPSILON, 10));
    glass_cone->closed = true;
    glass_cone->minimum = -1;
    glass_cone->maximum = 0;
    glass_cone->SetMaterial(glass_mat);
    w.add_object(glass_cone);

    Cylinder_ptr glass_cylinder{ std::make_shared<Cylinder>(Cylinder{}) };
    glass_cylinder->SetTransform(Math::Translation(1.8, 0.5 + EPSILON, 10) * Math::Scaling(0.5));
    glass_cylinder->minimum = -1;
    glass_cylinder->maximum = 1;
    glass_cylinder->closed = true;
    glass_cylinder->SetMaterial(glass_mat);
    w.add_object(glass_cylinder);



    //Initialize the Camera

    Camera c{1280, 720, 3 * (M_PI / 4)};

    //Position the Camera
    c.SetTransform(Math::ViewTransform(Point(3.67, 4, -20), Point(0, 0.5, 10), Vector(0, 1, 0)));
    //c.SetTransform(Math::ViewTransform(Point(0, 1, -20), Point(0, 1, 8), Vector(0, 1, 0)));

    c.SetSamplesPerPixel(20);

    c.depth_of_field = true;
    c.anti_aliasing = true;
    c.SetApertureSize(0.1);
    c.SetFocalLength(30.4256);

    //RenderMultiThread the image
    Canvas image = w.render_multi_thread(c,20);

    image.ToPPM();



}

