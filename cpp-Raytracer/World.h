//
// Created by Jean-Luc von Nessen on 24.01.22.
//
#pragma once

#include <vector>
#include "Light.h"
#include "Ray.h"
#include "Canvas.h"
#include "Camera.h"
#include "IntersectionComputations.h"


class World {
//Methods
private:

    color get_color_for_pixel(camera c, int x, int y);

    canvas execute_single_pass(camera c);
    canvas execute_multiple_passes(camera c, int num_passes);

    void print_progress_update() const;

public:

    static int get_recursion_depth(){ return m_recursion_depth; }
	static void set_recursion_depth(int new_depth){ m_recursion_depth = new_depth; }

    std::vector<point_light>& get_world_lights(){ return m_world_lights; }
    void add_light(point_light light);

    std::vector<shape_ptr>& get_world_objects(){ return m_world_objects; }
    void add_object(shape_ptr obj);

    std::vector<intersection> intersect_world(ray ray);

    bool calculate_shadow(point p);

    color calculate_reflected_color(intersection_computations comps, int remaining = m_recursion_depth);

    color calculate_refracted_color(intersection_computations comps, int remaining = m_recursion_depth);

    color shade_hit(intersection_computations comps, int remaining = m_recursion_depth);

    color calculate_color_at(ray r, int remaining = m_recursion_depth);

    canvas render_multi_thread(camera c, int num_threads);

//Members
private:

    static int m_recursion_depth;

    std::vector<point_light> m_world_lights{};

    std::vector<shape_ptr> m_world_objects{};

    static std::atomic<int> m_remaining_lines;
    int m_total_lines{0};

public:
};

World DefaultWorld();

