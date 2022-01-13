#include "Tracer.h"
#include "Color.h"
#include "Canvas.h"
#include <iostream>
#include <string>
#include "Sphere.h"
#include "Ray.h"

int main()
{

    ////The center of the canvas (50, 50) is (0, 0, 0)
    //Canvas c{ 100, 100 };
    //Color red{ 1, 0, 0 };

    ////12 oclock is (0, 0, 1),

    //Point p{ 0, 0, 1 };

    //for (int i = 0; i < 12; i++)
    //{
    //	//calculate rotation matrix for current Hour
    //	Matrix4 rotation = Math::Rotation_Y(i * (M_PI/6));
    //	Tuple p_current = rotation * p;
    //	p_current = p_current * 20;

    //	c.write_pixel(p_current.x + 50, p_current.z + 50, red);
    //}

    //c.to_ppm();

//    //Goal is to Draw a sphere.
//
//    //center of the canvas (50, 50) will be (0, 0, 0)
//    int canvas_size = 500;
//    Canvas c{ canvas_size, canvas_size };
//    Color red{ 1, 0, 0 };
//
//    //Create a sphere at (0,0,0) and move it back to (0,10,0)
//    Sphere sphere{ 0 };
//    Matrix4 translate = Math::Translation(canvas_size/2, 50, canvas_size/2);
//    Matrix4 scale = Math::Scaling(100, 100, 100);
//    Matrix4 transform = translate * scale;
//    sphere.SetTransform(transform);
//
//
//    //cast a ray from every pixel of the screen, directly in front
//    //100 pixels are 1 unit long??
//    for (int x = 0; x < canvas_size; x++)
//    {
//        for (int z = 0; z < canvas_size; z++)
//        {
//            Point ray_origin{ float(x), -1, float(z) };
//            Vector ray_direction{ 0, 1, 0 };
//
//            Ray ray{ ray_origin, ray_direction };
//
//            std::vector<Intersection> intersections = ray.Intersect(sphere);
//
//            if (!intersections.empty())
//            {
//                c.write_pixel(x , z , red);
//            }
//        }
//    }
//
//    c.to_ppm();
    //Color every pixel for which a hit was detected

    Sphere s{0};
    s.SetTransform(Math::Translation(0, 1, 0));
    Vector n = s.NormalAt(Point(0, 1.70711, -0.70711));

    std::cout << "X: " << n.x << " Y: " << n.y << " Z: " << n.z << std::endl;


    return 0;
}