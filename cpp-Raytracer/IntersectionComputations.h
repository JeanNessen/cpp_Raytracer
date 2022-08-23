//
// Created by Jean-Luc von Nessen on 03.02.22.
//

#pragma once


#include "Shapes/shape.h"
#include "Intersection.h"
#include "Ray.h"

//Data structure to hold precalculated Computations about an Intersection
struct IntersectionComputations {
    double t;
    const shape_ptr object;
    Point point;
    Vector eye_v;
    Vector normal_v;
    Vector reflect_v;
    bool inside;
    Point over_point, under_point;
    double n1, n2;

    IntersectionComputations(double pT, shape_ptr  pObject, Point pPoint, Vector pEyeV, Vector pNormalV, double pN1, double pN2);


};

IntersectionComputations PrepareComputations(const intersection& pIntersection, ray pRay, std::vector<intersection> xs = {});

std::vector<double> find_refractive_indices(const intersection& pIntersection, const std::vector<intersection>& xs);

double Schlick(const IntersectionComputations& comps);




