//
// Created by Jean-Luc von Nessen on 24.01.22.
//

#include "CWorld.h"

#include <iostream>
#include <chrono>
#include <algorithm>
//#include <omp.h>


//static variables
int CWorld::m_recursion_depth = 5;

CWorld DefaultWorld() {
    CWorld w{};

    SPointLight default_light{CColor(1, 1, 1), Point(-10, 10, -10)};
    w.AddLight(default_light);

    Sphere_ptr default_sphere_1 (new CSphere());
    default_sphere_1->GetMaterial().color = CColor(0.8, 1.0, 0.6);
    default_sphere_1->GetMaterial().diffuse = 0.7;
    default_sphere_1->GetMaterial().specular = 0.2;

    w.AddObject(default_sphere_1);

    Sphere_ptr default_sphere_2 (new CSphere());
    default_sphere_2->SetTransform(Math::Scaling(0.5, 0.5, 0.5));

    w.AddObject(default_sphere_2);

    return w;
}

void CWorld::AddLight(SPointLight light) {
    m_world_lights.push_back(light);
}

void CWorld::AddObject(Shape_ptr obj) {
    m_world_objects.push_back(obj);
}

std::vector<SIntersection> CWorld::IntersectWorld(CRay ray) {

    std::vector<std::unique_ptr<SIntersection>> world_intersections_ptr;

    //Add all the intersections to the vector
    for (const auto& obj: m_world_objects) {
        std::vector<SIntersection> intersections = ray.Intersect(obj);

        for (auto i: intersections) {
            world_intersections_ptr.push_back(std::make_unique<SIntersection>(i));
        }
    }

    //Sort the pointer vector
    std::sort(world_intersections_ptr.begin(), world_intersections_ptr.end(), [](std::unique_ptr<SIntersection>& lhs, std::unique_ptr<SIntersection>& rhs) {
        return lhs->t > rhs->t;
    });

    //Make new vector with sorted Intersections
    std::vector<SIntersection> world_intersections;

    world_intersections.reserve(world_intersections_ptr.size());

    //Reverse the Vector
    for (int i = 0; i < world_intersections_ptr.size(); ++i) {
        world_intersections.push_back(*(world_intersections_ptr[world_intersections_ptr.size()-i-1]));
    }

    return world_intersections;
}

CColor CWorld::ShadeHit(SIntersectionComputations comps, int remaining) {
    CColor surface = Lighting(comps.object->GetMaterialConst(),
                              comps.object,
                              m_world_lights[0],
                              comps.over_point,
                              comps.eye_v,
                              comps.normal_v,
                              CalculateShadow(comps.over_point));

    CColor reflected = CalculateReflectedColor(comps, remaining);
    CColor refracted = CalculateRefractedColor(comps, remaining);

    CMaterial material = comps.object->GetMaterial();
    if (material.reflective > 0 && material.transparency > 0)
    {
        double reflectance = Schlick(comps);
        return surface + reflected * reflectance + refracted * (1-reflectance);
    }
    else
    {
        return surface + reflected + refracted;

    }
}

CColor CWorld::CalculateColorAt(CRay r, int remaining) {

    std::vector<SIntersection> intersections = IntersectWorld(r);

    if(!intersections.empty() && Hit(intersections))
    {
        SIntersection hit = *Hit(intersections);
        SIntersectionComputations comps = PrepareComputations(hit, r);
        CColor color = ShadeHit(comps, remaining);
        return color;
    }
    else
    {
        return color::black;
    }

}

CCanvas CWorld::RenderSingleThread(CCamera c) {

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Starting render using one thread." << std::endl;

    CCanvas image_sum{c.GetHSize(), c.GetVSize()};

    {
        for (int i = 0; i < c.GetSamplesPerPixel(); ++i) {
            std::cout << "Starting render pass " << i + 1 << " of " << c.GetSamplesPerPixel() << "." << std::endl;
            image_sum += ExecuteRenderPass(c);
            std::cout << "Finished render pass " << i + 1 << "." << std::endl;
        }
    }
    CCanvas image_average = image_sum / c.GetSamplesPerPixel();



    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    double seconds = duration.count() / 1000.0f;

    std::cout << "Finished in " << seconds << " seconds with " << c.GetSamplesPerPixel()  << " samples per pixel on one" << " thread." << std::endl;

    return image_average;
}


CCanvas CWorld::ExecuteRenderPass(CCamera c) {
    CCanvas image{c.GetHSize(), c.GetVSize()};

    int lines_remaining = c.GetVSize();

#pragma omp parallel
    {
    #pragma omp for
        for (int y = 0; y < c.GetVSize()-1; ++y) {
                for (int x = 0; x < c.GetHSize(); ++x) {
                    CColor color = GetColorForPixel(c, x, y);
                    image.WritePixel(x, y, color);
                }
            PrintProgressUpdate(c.GetVSize(), --lines_remaining, c);
        }
    }
    return image;
}

bool CWorld::CalculateShadow(Point p) {
    Vector v_point_to_light{m_world_lights[0].position - p};
    double distance_to_light = (v_point_to_light).magnitude();
    Vector direction_to_light = v_point_to_light.normalized();

    CRay r_point_to_light{p, direction_to_light};

    std::vector<SIntersection> intersections = IntersectWorld(r_point_to_light);

    if(SIntersection* hit = Hit(intersections))
    {
        bool blocking_shape_throws_shadow = hit->object->GetMaterial().throws_shadow;
        if (hit->t < distance_to_light && blocking_shape_throws_shadow)
        {
            return true;
        }
    }

    return false;
}

CColor CWorld::CalculateReflectedColor(SIntersectionComputations comps, int remaining) {
    if(comps.object->GetMaterial().reflective == 0 || remaining <= 0)
    {
        return color::black;
    } else
    {
        CRay reflected_ray{comps.over_point, comps.reflect_v};
        CColor color = CalculateColorAt(reflected_ray, remaining - 1);

        return color * comps.object->GetMaterial().reflective;
    }
}

CColor CWorld::GetColorForPixel(CCamera c, int x, int y) {
    CRay r = c.RayForPixel(x, y);
    CColor pixel_color = CalculateColorAt(r);
    return pixel_color;
}

void CWorld::PrintProgressUpdate(int lines_total, int lines_remaining, CCamera c) {
    if (lines_remaining % 10 == 0)
    {
        double remaining_percentage = double(lines_remaining) / double(lines_total);
        double progress_percentage = 100 - remaining_percentage * 100;

        std::cout.precision(4);
        std::cout << "Progress: " << progress_percentage << "%" << std::endl;
    }
}

CColor CWorld::CalculateRefractedColor(SIntersectionComputations comps, int remaining)
{
    //Aplly snells law to check for total internal reflection
    double n_ratio = comps.n1 / comps.n2;
    double cos_i = Math::Dot(comps.eye_v, comps.normal_v);
    double sin2_t = std::pow(n_ratio, 2) * (1 - std::pow(cos_i, 2));



    if (comps.object->GetMaterial().transparency == 0)
    {
        return color::black;
    }
    else if(remaining == 0)
    {
        return color::black;
    }
    else if(sin2_t > 1)
    {
        return color::black;
    }
    else
    {
        double cos_t = sqrt(1 - sin2_t);

        Vector direction {comps.normal_v * (n_ratio * cos_i - cos_t) -
                comps.eye_v * n_ratio};

        CRay refracted_ray{comps.under_point, direction};

        return CalculateColorAt(refracted_ray, remaining - 1) * comps.object->GetMaterial().transparency;
    }
}




