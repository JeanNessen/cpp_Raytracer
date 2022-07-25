//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_COMP_H
#define CPP_RAYTRACER_COMP_H

#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

//Data structure to hold precalculated Computations about an Intersection
struct IntersectionComputations {
    double t;
    const Shape_ptr object;
    Point point;
    Vector eye_v;
    Vector normal_v;
    Vector reflect_v;
    bool inside;
    Point over_point, under_point;
    double n1, n2;

    IntersectionComputations(double t, Shape_ptr  object, Point point, Vector eye_v, Vector normal_v, double n1, double n2);


};

IntersectionComputations PrepareComputations(const Intersection& intersection, Ray ray, std::vector<Intersection> xs = {});

std::vector<double> FindRefractiveIndices(const Intersection& intersection, const std::vector<Intersection>& xs);

double Schlick(const IntersectionComputations& comps);


#endif //CPP_RAYTRACER_COMP_H

