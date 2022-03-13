//
// Created by Jean-Luc von Nessen on 13.02.22.
//
#pragma once

#include "Math.h"

class CRay;

class CCamera {

//Methods
public:
    CCamera(int h_size, int v_size, double fov);


    [[nodiscard]] int GetHSize() const{return m_horizontalSize;}
    void SetHSize(int h){ m_horizontalSize = h;}

    [[nodiscard]] int GetVSize() const{return m_verticalSize;}
    void SetVSize(int v){ m_verticalSize = v;}

    [[nodiscard]] double GetFOV() const{return m_fieldOfView;}
    void SetFOV(double fov){ m_fieldOfView = fov;}

    Matrix4 GetTransform(){return m_transform;}
    void SetTransform(Matrix4 t){ m_transform = t;}

    [[nodiscard]] double GetApertureSize() const{ return m_apertureSize; }
    void SetApertureSize(double new_aperture_size){ m_apertureSize = new_aperture_size; }

    [[nodiscard]] double GetFocalLength() const{ return m_focalLength; }
    void SetFocalLength(double new_focal_length){ m_focalLength = new_focal_length; }

    [[nodiscard]] int GetSamplesPerPixel() const{ return m_samplesPerPixel; }
    void SetSamplesPerPixel(int samples){ m_samplesPerPixel = samples; }

    [[nodiscard]] double GetPixelSize() const{return m_pixel_size;}

    CRay RayForPixel(int x, int y);


private:
    void CalculatePixelSize();

    Point CalculateRayOrigin();

    [[nodiscard]] double CalculatePixelOffset(int pixel) const;


    [[nodiscard]] Point GetRandomPointOnAperture() const;


//Members
public:
    bool anti_aliasing = false;
    bool depth_of_field = false;

private:
    int m_horizontalSize;
    int m_verticalSize;
    double m_fieldOfView;
    double m_focalLength = 5;
    double m_apertureSize = 0.1;
    Matrix4 m_transform;
    int m_samplesPerPixel = 10;

    double m_pixel_size;
    double m_half_width;
    double m_half_height;
};

