//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#include "Camera.h"
#include "Ray.h"
#include <random>

Camera::Camera(int h_size, int v_size, double fov):
        m_horizontalSize(h_size),
        m_verticalSize(v_size),
        m_fieldOfView(fov),
        m_transform(Math::identiy_matrix)
{
    CalculatePixelSize();
}

void Camera::CalculatePixelSize() {
    double half_view = std::tan(m_fieldOfView / 2);

    double aspect = double(m_horizontalSize) / double(m_verticalSize);

    if (aspect >= 1)
    {
        m_half_width = half_view;
        m_half_height = half_view / aspect;
    } else
    {
        m_half_width = half_view * aspect;
        m_half_height = half_view;
    }

    m_pixel_size = (m_half_width * 2) / m_horizontalSize;
}

Ray Camera::RayForPixel(int x, int y) {
    //The offset from the edge of the canvas to a point in the pixel
    double x_offset = CalculatePixelOffset(x);
    double y_offset = CalculatePixelOffset(y);

    //The untransformed coordinates of the pixel in world space
    double world_x = m_half_width - x_offset;
    double world_y = m_half_height - y_offset;

    //Using the camera matrix, m_transform the canvas point and the origin, and then compute the ray's direction vector, the canvas is at z = -m_focalLength
    Point pixel{m_transform.Inversed() * Point(world_x, world_y, -m_focalLength)};

    Point origin = CalculateRayOrigin();

    Vector direction{Vector{pixel - origin}.normalized()};

    return {origin, direction};
}

double Camera::CalculatePixelOffset(int pixel) const {
    double offset;
    //If Anti Aliasing is enabled the ray will pass through a random point inside the pixel.
    if(anti_aliasing)
    {
        offset = (double(pixel) + Math::GetRandomDouble(0, 1)) * m_pixel_size;
    }
    //If Anti Aliasing is disabled the ray will pass through the center of the pixel.
    else
    {
        offset = (double(pixel) + 0.5f) * m_pixel_size;
    }
    return offset;
}

Point Camera::CalculateRayOrigin() {
    Point origin;
    //If Depth of field is enabled, the ray will originate from a random point on the aperture
    if(depth_of_field)
    {
        origin = Point{m_transform.Inversed() * GetRandomPointOnAperture()};
    }
    //If Depth of field is disabled, the ray will originate from (0, 0, 0)
    else
    {
        origin = Point{m_transform.Inversed() * Point(0, 0, 0)};
    }
    return origin;
}



Point Camera::GetRandomPointOnAperture() const {
    double x = Math::GetRandomDouble(0, m_apertureSize) - (m_apertureSize / 2);
    double y = Math::GetRandomDouble(0, m_apertureSize) - (m_apertureSize / 2);

    return {x, y, 0};
}
