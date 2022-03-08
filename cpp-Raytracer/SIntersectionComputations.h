//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#ifndef CPP_RAYTRACER_COMP_H
#define CPP_RAYTRACER_COMP_H

#include "CShape.h"
#include "SIntersection.h"
#include "CRay.h"

//Data structure to hold precalculated Computations about an SIntersection
struct SIntersectionComputations {
    double t;
    const Shape_ptr object;
    Point point;
    Vector eye_v;
    Vector normal_v;
    Vector reflect_v;
    bool inside;
    Point over_point, under_point;
    double n1, n2;

    SIntersectionComputations(double t, Shape_ptr  object, Point point, Vector eye_v, Vector normal_v, double n1, double n2);


};

SIntersectionComputations PrepareComputations(const SIntersection& intersection, CRay ray, std::vector<SIntersection> xs = {});

std::vector<double> FindRefractiveIndices(const SIntersection& intersection, const std::vector<SIntersection>& xs);

double Schlick(const SIntersectionComputations& comps);


#endif //CPP_RAYTRACER_COMP_H

