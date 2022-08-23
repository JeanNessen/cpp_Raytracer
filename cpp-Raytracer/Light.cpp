//
// Created by Jean-Luc von Nessen on 13.01.22.
//

#include "Light.h"

color Lighting(Material m, shape_ptr object, PointLight light, Point position, Vector eye_v, Vector normal_v, bool in_shadow) {

    color light_color;

    //check if the material has a m_pattern
    if(m.GetPattern())
    {
        light_color = object->stripe_at_object(position);
    } else
    {
        light_color = m.color;
    }

    //Combine surface color with lights intensity/color
    color effective_color = light_color * light.intensity;

    if(in_shadow)
    {
        //If the point is in shadow, only the ambient light will affect it
        color ambient = effective_color * m.ambient;

        return ambient;
    }
    else
    {
        //Find the direction to the light source
        Vector light_v = Vector(light.position - position).normalized();

        //Compute the ambient contribution
        color ambient = effective_color * m.ambient;

        //light_dot_normal represents the cosine of the angle between
        //the light vector and the normal vector. A negative number means the
        //light is on the other side of the surface
        double light_dot_normal = Math::Dot(light_v, normal_v);

        color diffuse{0, 0, 0};
        color specular{0, 0, 0};

        if (light_dot_normal >= 0)
        {
            //compute the diffuse contribution
            diffuse = effective_color * m.diffuse * light_dot_normal;

            //reflect_dot_eye represents the cosine of the angle between the
            //reflection vector and the eye vector. A negative number means the
            //light reflects away from it

            Vector reflect_v{-light_v.Reflect(normal_v)};
            double reflect_dot_eye = Math::Dot(reflect_v, eye_v);

            if(reflect_dot_eye <= 0)
            {
                specular = color(0, 0, 0);
            } else
            {
                double factor = std::pow(reflect_dot_eye, m.shininess);
                specular = light.intensity * m.specular * factor;
            }
        }
        //Add the three contributions together to get the final shading
        return ambient + diffuse + specular;
    }
}

bool PointLight::operator==(const PointLight &other) const {
    if (intensity == other.intensity && position == other.position)
    {
        return true;
    }
    return false;
}
