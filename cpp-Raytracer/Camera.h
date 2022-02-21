//
// Created by Jean-Luc von Nessen on 13.02.22.
//

#ifndef CPP_RAYTRACER_CAMERA_H
#define CPP_RAYTRACER_CAMERA_H

#include "Math.h"
#include "Ray.h"

class Camera {
private:
    int horizontal_size;
    int vertical_size;
    float field_of_view;
    Matrix4 transform;

    float pixel_size;
    float half_width, half_height;

    void CalculatePixelSize();

public:
    Camera(int h_size, int v_size, float fov);

    int GetHSize() const{return horizontal_size;}
    void SetHSize(int h){horizontal_size = h;}

    int GetVSize() const{return vertical_size;}
    void SetVSize(int v){vertical_size = v;}

    float GetFOV() const{return field_of_view;}
    void SetFOV(float fov){field_of_view = fov;}

    Matrix4 GetTransform(){return transform;}
    void SetTransform(Matrix4 t){ transform = t;}

    float GetPixelSize() const{return pixel_size;}

    Ray RayForPixel(int x, int y);
};


#endif //CPP_RAYTRACER_CAMERA_H
