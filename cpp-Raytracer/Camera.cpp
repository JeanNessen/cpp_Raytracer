//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#include "Camera.h"
#include <random>

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
    Point pixel{transform.Inversed() * Point(world_x, world_y, -focal_length)};

    //Origin for pinhole camera
    Point origin{transform.Inversed() * Point(0, 0, 0)};

    //Origin for camera with aperture
    //Point origin{transform.Inversed() * GetRandomPointOnAperture()};

    Vector direction{Vector{pixel - origin}.normalized()};

    return Ray(origin, direction);
}



Point Camera::GetRandomPointOnAperture() {
    std::random_device dev;
    std::uniform_real_distribution<double> distribution(0.0, aperture_size);
    std::mt19937 generator(dev());
    double x = distribution(generator) - (aperture_size / 2);
    double y = distribution(generator) - (aperture_size / 2);

    return {x, y, 0};
}

Ray Camera::RandomRayForPixel(int x, int y) {
    //The offset from the edge of the canvas to the CENTER of the pixel
    double x_offset = (double(x) + GetRandomDouble(0, 1)) * pixel_size;
    double y_offset = (double(y) + GetRandomDouble(0, 1)) * pixel_size;

    //The untransformed coordinates of the pixel in world space
    double world_x = half_width - x_offset;
    double world_y = half_height - y_offset;

    //Using the camera matrix, transform the canvas point and the origin, and then compute the rays direction vector, the canvas is at z = -1
    Point pixel{transform.Inversed() * Point(world_x, world_y, -focal_length)};

    //Origin for camera with aperture
    Point origin{transform.Inversed() * GetRandomPointOnAperture()};

    Vector direction{Vector{pixel - origin}.normalized()};

    return Ray(origin, direction);
}

double Camera::GetRandomDouble(double min, double max) {
    std::random_device dev;
    std::uniform_real_distribution<double> distribution(min, max);
    std::mt19937 generator(dev());
    double a = distribution(generator);
    return a;
}
