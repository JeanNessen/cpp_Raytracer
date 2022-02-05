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


int main()
{


//    //Goal is to Draw a sphere.
//
//    //center of the canvas (50, 50) will be (0, 0, 0)
//    const int canvas_size = 500;
//    Canvas c{ canvas_size, canvas_size };
//    Color red{1, 0, 0};
//
//    //Create a sphere at (0,0,0) and move it back to (0,10,0)
//    Sphere sphere{ 0 };
//    Material sphere_mat{};
//    sphere_mat.color = Color(1, 0.2, 1);
//    sphere.SetMaterial(sphere_mat);
//
//    //Create a light source
//    Point light_position{-10, 10, -10};
//    Color light_color{1, 1, 1};
//    PointLight light{light_color, light_position};
//
//    Matrix4 translate = Math::Translation(canvas_size/2, 50, canvas_size/2);
//    Matrix4 scale = Math::Scaling(100, 100, 100);
//    Matrix4 transform = translate * scale;
//    //sphere.SetTransform(transform);
//
//    //Start the ray at z=-5
//    Point ray_origin{ 0, 0, -5 };
//
//    //Z position of the Wall to cast the rays to (canvas)
//    const float wall_z = 10;
//    const float wall_size = 7;
//    const float pixel_size = wall_size / canvas_size;
//    const float half = wall_size / 2;
//
//
//    //cast a ray from every pixel of the screen, directly in front
//    //100 pixels are 1 unit long??
//    for (int y = 0; y < canvas_size; y++)
//    {
//        float world_y = half - pixel_size * y;
//        for (int x = 0; x < canvas_size; x++)
//        {
//            float world_x = -half + pixel_size * x;
//
//            //describe the point on the wall that the ray will target
//            Point position{world_x, world_y, wall_z};
//
//            Vector ray_direction{position - ray_origin};
//
//            Ray ray{ ray_origin, ray_direction.normalized() };
//
//            std::vector<Intersection> intersections = ray.Intersect(sphere);
//
//            if (!intersections.empty())
//            {
//                auto hit = *Hit(intersections);
//                Point point = ray.Position(hit.t);
//                Vector normal = hit.object.NormalAt(point);
//                Vector eye{-ray.direction};
//                Color color = Lighting(hit.object.GetMaterial(), light, point, eye, normal);
//                c.write_pixel(x , y , color);
//            }
//        }
//    }
//
//    c.to_ppm();

    World w = DefaultWorld();
    Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

    std::vector<Intersection> xs = w.IntersectWorld(r);

    for (Intersection i: xs) {
        std::cout << i.t << std::endl;
    }

    return 0;
}