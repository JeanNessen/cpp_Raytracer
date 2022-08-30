//
// Created by Jean-Luc von Nessen on 13.02.22.
//
#pragma once

#include "Math.h"

class ray;

class camera {

//Methods
public:
    camera(int pHSize, int pVSize, double pFOV);


    [[nodiscard]] int get_h_size() const{return m_horizontal_size;}
    void set_h_size(const int pH){ m_horizontal_size = pH;}

    [[nodiscard]] int get_v_size() const{return m_vertical_size;}
    void set_v_size(const int pV){ m_vertical_size = pV;}

    [[nodiscard]] double get_fov() const{return m_field_of_view;}
    void set_fov(const double pFov){ m_field_of_view = pFov;}

	[[nodiscard]] Matrix4 get_transform() const {return m_transform;}
    void set_transform(const Matrix4 pT){ m_transform = pT;}

    [[nodiscard]] double get_aperture_size() const{ return m_aperture_size; }
    void set_aperture_size(const double pNewApertureSize){ m_aperture_size = pNewApertureSize; }

    [[nodiscard]] double get_focal_length() const{ return m_focal_length; }
    void set_focal_length(const double pNewFocalLength){ m_focal_length = pNewFocalLength; }

    [[nodiscard]] int get_samples_per_pixel() const{ return m_samples_per_pixel; }
    void set_samples_per_pixel(const int pSamples){ m_samples_per_pixel = pSamples; }

    [[nodiscard]] double get_pixel_size() const{return m_pixel_size;}

	[[nodiscard]] ray ray_for_pixel(int pX,int pY) const;


private:
    void calculate_pixel_size();

	[[nodiscard]] point calculate_ray_origin() const;

    [[nodiscard]] double calculate_pixel_offset(int pPixel) const;


    [[nodiscard]] point get_random_point_on_aperture() const;


//Members
public:
    bool anti_aliasing = false;
    bool depth_of_field = false;

private:
    int m_horizontal_size;
    int m_vertical_size;
    double m_field_of_view;
    double m_focal_length = 5;
    double m_aperture_size = 0.1;
    Matrix4 m_transform;
    int m_samples_per_pixel = 10;

    double m_pixel_size;
    double m_half_width;
    double m_half_height;
};

