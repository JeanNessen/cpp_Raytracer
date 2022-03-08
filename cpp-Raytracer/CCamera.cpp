//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#include "CCamera.h"
#include <random>

CCamera::CCamera(int h_size, int v_size, double fov):
    horizontal_size(h_size),
    vertical_size(v_size),
    field_of_view(fov),
    transform(Math::identiy_matrix)
{
    CalculatePixelSize();
}

void CCamera::CalculatePixelSize() {
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

CRay CCamera::RayForPixel(int x, int y) {
    //The offset from the edge of the canvas to a point in the pixel
    double x_offset = CalculatePixelOffset(x);
    double y_offset = CalculatePixelOffset(y);

    //The untransformed coordinates of the pixel in world space
    double world_x = half_width - x_offset;
    double world_y = half_height - y_offset;

    //Using the camera matrix, transform the canvas point and the origin, and then compute the rays direction vector, the canvas is at z = -1
    Point pixel{transform.Inversed() * Point(world_x, world_y, -focal_length)};

    Point origin = CalculateRayOrigin();

    Vector direction{Vector{pixel - origin}.normalized()};

    return {origin, direction};
}

double CCamera::CalculatePixelOffset(int pixel) const {
    double offset;
    //If Anti Aliasing is enabled the ray will pass through a random point inside the pixel.
    if(anti_aliasing)
    {
        offset = (double(pixel) + Math::GetRandomDouble(0, 1)) * pixel_size;
    }
    //If Anti Aliasing is disabled the ray will pass through the center of the pixel.
    else
    {
        offset = (double(pixel) + 0.5f) * pixel_size;
    }
    return offset;
}

Point CCamera::CalculateRayOrigin() {
    Point origin;
    //If Depth of field is enabled, the ray will originate from a random point on the aperture
    if(depth_of_field)
    {
        origin = Point{transform.Inversed() * GetRandomPointOnAperture()};
    }
    //If Depth of field is disabled, the ray will originate from (0, 0, 0)
    else
    {
        origin = Point{transform.Inversed() * Point(0, 0, 0)};
    }
    return origin;
}



Point CCamera::GetRandomPointOnAperture() const {
    double x = Math::GetRandomDouble(0, aperture_size) - (aperture_size / 2);
    double y = Math::GetRandomDouble(0, aperture_size) - (aperture_size / 2);

    return {x, y, 0};
}
