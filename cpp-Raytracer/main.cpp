#include "Canvas.h"
#include "world.h"
#include <random>

bool CheckSpot(point spot, const std::vector<point>& taken_spots)
{
    double max_distance = 0.5;
    bool spot_is_free = true;
    for(point s: taken_spots)
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

void PlaceSpheres(world &w)
{
    std::vector<point> taken_spots;

    for (int i = 0; i < 25; ++i) {
        sphere_ptr sphere(new Sphere());
        sphere->get_material().color = color(Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1), Math::GetRandomDouble(0, 1));
        sphere->get_material().diffuse = 0.7f;
        sphere->get_material().specular = 0.2f;
        sphere->get_material().reflective = 0.1;
        sphere->get_material().shininess = 150;
        double sphere_scaling_s = Math::GetRandomDouble(0.1, 0.25);
        matrix4 scaling = Math::Scaling(sphere_scaling_s);
        point spot{Math::GetRandomDouble(-5, 5), sphere_scaling_s, Math::GetRandomDouble(10, 20)};
        while(!CheckSpot(spot, taken_spots))
        {
            spot = point{Math::GetRandomDouble(-5, 5), sphere_scaling_s, Math::GetRandomDouble(10, 20)};
        }
        taken_spots.push_back(spot);
        sphere->set_transform(Math::Translation(spot.x, spot.y, spot.z) * scaling);
        w.add_object(sphere);
    }
}

int main()
{
    //Initialize the World
    world w{};
    w.set_recursion_depth(5);

    //Initialize the light
    point_light default_light{ color{254.0/255.0, 216.0/255.0, 177.0/255.0}, point(0, 6, 0) };
    w.add_light(default_light);


    //Set up the m_pattern for the floor
    std::shared_ptr<Pattern> p(new checkers_pattern(color(0.8, 0.8, 0.8), color(0.4, 0.4, 0.4)));
    p->SetTransform(Math::Scaling(2));

    //Set up the floor
    plane_ptr floor (new plane());
    floor->get_material().color = colors::white;
    floor->get_material().specular = 0.0f;
    floor->get_material().reflective = 0.01f;
    w.add_object(floor);

    //Set up ceiling
    cube_ptr ceiling(std::make_shared<cube>(cube()));
    ceiling->get_material().color = colors::white;
    ceiling->get_material().specular = 0.0f;
    ceiling->get_material().reflective = 0.01f;
    ceiling->set_transform(Math::Translation(0, 10, 0) * Math::Scaling(10, 0.5, 11));
    w.add_object(ceiling);

    //Set up right wall
    cube_ptr right_wall(std::make_shared<cube>(cube()));
    right_wall->get_material().color = colors::green;
    right_wall->get_material().specular = 0.0f;
    right_wall->get_material().reflective = 0.01f;
    right_wall->set_transform(Math::Translation(5, 0, 0)* Math::Scaling(0.5, 11, 11));
    w.add_object(right_wall);

    //Set up left wall
    cube_ptr left_wall(std::make_shared<cube>(cube()));
    left_wall->get_material().color = colors::red;
    left_wall->get_material().specular = 0.0f;
    left_wall->get_material().reflective = 0.01f;
    left_wall->set_transform( Math::Translation(-5, 0, 0) * Math::Scaling(0.5, 11, 11));
    w.add_object(left_wall);

    //Set up back wall
    cube_ptr back_wall(std::make_shared<cube>(cube()));
    back_wall->get_material().color = colors::white;
    back_wall->get_material().specular = 0.0f;
    back_wall->get_material().reflective = 0.01f;
    back_wall->set_transform(Math::Translation(0, 0, 5) * Math::Scaling(11, 11, 0.5));
    w.add_object(back_wall);


    //Add first cube
    cube_ptr cube_1(std::make_shared<cube>(cube()));
    cube_1->get_material().color = colors::white;
    cube_1->get_material().specular = 0.0f;
    cube_1->get_material().reflective = 0.01f;
    cube_1->set_transform(Math::Translation(2.5, 1, 0.5) * Math::Rotation_Y(-50) * Math::Scaling(1, 2, 1));
    w.add_object(cube_1);



    //Set Glass material
    material glass_mat{};
    glass_mat.color = colors::black;
    glass_mat.transparency = 0.8;
    glass_mat.refractive_index = 1.51;
    glass_mat.reflective = 1;
    glass_mat.diffuse = 0.25;
    glass_mat.ambient = 0.25;
    glass_mat.specular = 1;
    glass_mat.shininess = 300;
    glass_mat.throws_shadow = false;





    //Initialize the Camera

    camera c{1000, 1000, 3 * (M_PI / 4)};

    //Position the Camera
    c.set_transform(Math::ViewTransform(point(0, 5, -29.5), point(0, 5, 0), vector(0, 1, 0)));
    //c.SetTransform(Math::ViewTransform(point(0, 1, -20), point(0, 1, 8), vector(0, 1, 0)));

    c.set_samples_per_pixel(20);

    c.depth_of_field = false;
    c.anti_aliasing = true;
    c.set_aperture_size(0.5);
    c.set_focal_length(10);

    //RenderMultiThread the image
    canvas image = w.render_multi_thread(c,20);

    image.to_ppm();



}

