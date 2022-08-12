//
// Created by Jean-Luc von Nessen on 24.01.22.
//
#pragma once

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Ray.h"
#include "Canvas.h"
#include "Camera.h"
#include "IntersectionComputations.h"


class World {
//Methods
private:

    Color get_color_for_pixel(Camera c, int x, int y);

    Canvas execute_single_pass(Camera c);
    Canvas execute_multiple_passes(Camera c, int num_passes);

    void print_progress_update() const;

public:

    static int get_recursion_depth(){ return m_recursion_depth; }
	static void set_recursion_depth(int new_depth){ m_recursion_depth = new_depth; }

    std::vector<PointLight>& get_world_lights(){ return m_world_lights; }
    void add_light(PointLight light);

    std::vector<Shape_ptr>& get_world_objects(){ return m_world_objects; }
    void add_object(Shape_ptr obj);

    std::vector<Intersection> intersect_world(Ray ray);

    bool calculate_shadow(Point p);

    Color calculate_reflected_color(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color calculate_refracted_color(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color shade_hit(IntersectionComputations comps, int remaining = m_recursion_depth);

    Color calculate_color_at(Ray r, int remaining = m_recursion_depth);

    Canvas render_multi_thread(Camera c, int num_threads);

//Members
private:

    static int m_recursion_depth;

    std::vector<PointLight> m_world_lights{};

    std::vector<Shape_ptr> m_world_objects{};

    static std::atomic<int> m_remaining_lines;
    int m_total_lines{0};

public:
};

World DefaultWorld();

