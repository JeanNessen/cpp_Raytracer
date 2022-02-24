//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#include "Camera.h"

Camera::Camera(int h_size, int v_size, double fov):
    horizontal_size(h_size),
    vertical_size(v_size),
    field_of_view(fov),
    transform(Math::identiy_matrix)
{
    CalculatePixelSize();
}

void Camera::CalculatePixelSize() {
    double half_view = std::tan(field_of_view / 2);

    double aspect = double(horizontal_size) / double(vertical_size);

    if (aspect >= 1)
    {
        half_width = half_view;
        half_height = half_view / aspect;
    } else
    {
        half_width = half_view * aspect;
        half_height = half_view;
    }

    pixel_size = (half_width * 2) / horizontal_size;
}

Ray Camera::RayForPixel(int x, int y) {
    //The offset from the edge of the canvas to the CENTER of the pixel
    double x_offset = (double(x) + 0.5f) * pixel_size;
    double y_offset = (double(y) + 0.5f) * pixel_size;

    //The untransformed coordinates of the pixel in world space
    double world_x = half_width - x_offset;
    double world_y = half_height - y_offset;

    //Using the camera matrix, transform the canvas point and the origin, and then compute the rays direction vector, the canvas is at z = -1
    Point pixel{transform.Inversed() * Point(world_x, world_y, -1)};
    Point origin{transform.Inversed() * Point(0, 0, 0)};
    Vector direction{Vector{pixel - origin}.normalized()};

    return Ray(origin, direction);
}
