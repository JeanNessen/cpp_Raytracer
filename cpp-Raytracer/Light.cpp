//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#include "Light.h"

Color Lighting(Material m, PointLight light, Point position, Vector eye_v, Vector normal_v) {
    //Combine surface color with lights intensity/color
    Color effective_color = m.color * light.intensity;

    //Find the direction to the light source
    Vector light_v = Vector(light.position - position).normalized();

    //Compute the ambient contribution
    Color ambient = effective_color * m.ambient;

    //light_dot_normal represents the cosine of the angle between
    //the light vector and the normal vector. A negative number means the
    //light is on the other side of the surface
    float light_dot_normal = Math::Dot(light_v, normal_v);

    Color diffuse{0, 0, 0};
    Color specular{0, 0, 0};

    if (light_dot_normal >= 0)
    {
        //compute the diffuse contribution
        diffuse = effective_color * m.diffuse * light_dot_normal;

        //reflect_dot_eye represents the cosine of the angle between the
        //reflection vector and the eye vector. A negative number means the
        //light reflects away from it

        Vector reflect_v{-light_v.Reflect(normal_v)};
        float reflect_dot_eye = Math::Dot(reflect_v, eye_v);

        if(reflect_dot_eye <= 0)
        {
            specular = Color(0, 0, 0);
        } else
        {
            float factor = std::pow(reflect_dot_eye, m.shininess);
            specular = light.intensity * m.specular * factor;
        }
    }
    //Add the three contributions together to get the final shading
    return ambient + diffuse + specular;
}
