//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#include "Camera.h"
#include "Ray.h"
#include <random>

camera::camera(const int pHSize, const int pVSize, const double pFOV):
        m_horizontal_size(pHSize),
        m_vertical_size(pVSize),
        m_field_of_view(pFOV),
        m_transform(Math::identiy_matrix)
{
    calculate_pixel_size();
}

void camera::calculate_pixel_size() {
	const double halfView = std::tan(m_field_of_view / 2);

	const double aspect = static_cast<double>(m_horizontal_size) / static_cast<double>(m_vertical_size);

    if (aspect >= 1)
    {
        m_half_width = halfView;
        m_half_height = halfView / aspect;
    } else
    {
        m_half_width = halfView * aspect;
        m_half_height = halfView;
    }

    m_pixel_size = (m_half_width * 2) / m_horizontal_size;
}

ray camera::ray_for_pixel(const int pX, const int pY) const
{
    //The offset from the edge of the canvas to a point in the pixel
    const double xOffset = calculate_pixel_offset(pX);
    const double yOffset = calculate_pixel_offset(pY);

    //The untransformed coordinates of the pixel in world space
    const double worldX = m_half_width - xOffset;
    const double worldY = m_half_height - yOffset;

    //Using the camera matrix, m_transform the canvas point and the origin, and then compute the ray's direction vector, the canvas is at z = -m_focalLength
    const Point pixel{m_transform.Inversed() * Point(worldX, worldY, -m_focal_length)};

    Point origin = calculate_ray_origin();

    Vector direction{Vector{pixel - origin}.normalized()};

    return {origin, direction};
}

double camera::calculate_pixel_offset(const int pPixel) const {
    double offset;
    //If Anti Aliasing is enabled the ray will pass through a random point inside the pixel.
    if(anti_aliasing)
    {
        offset = (static_cast<double>(pPixel) + Math::GetRandomDouble(0, 1)) * m_pixel_size;
    }
    //If Anti Aliasing is disabled the ray will pass through the center of the pixel.
    else
    {
        offset = (static_cast<double>(pPixel) + 0.5) * m_pixel_size;
    }
    return offset;
}

Point camera::calculate_ray_origin() const
{
    Point origin;
    //If Depth of field is enabled, the ray will originate from a random point on the aperture
    if(depth_of_field)
    {
        origin = Point{m_transform.Inversed() * get_random_point_on_aperture()};
    }
    //If Depth of field is disabled, the ray will originate from (0, 0, 0)
    else
    {
        origin = Point{m_transform.Inversed() * Point(0, 0, 0)};
    }
    return origin;
}



Point camera::get_random_point_on_aperture() const {
    double x = Math::GetRandomDouble(0, m_aperture_size) - (m_aperture_size / 2);
    double y = Math::GetRandomDouble(0, m_aperture_size) - (m_aperture_size / 2);

    return {x, y, 0};
}
