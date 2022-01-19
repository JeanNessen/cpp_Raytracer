cmake_minimum_required(VERSION 3.21)
project(cpp_Raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_Raytracer cpp-Raytracer/main.cpp
        cpp-Raytracer/Math.cpp cpp-Raytracer/Math.h
        cpp-Raytracer/Canvas.cpp cpp-Raytracer/Canvas.h
        cpp-Raytracer/Color.cpp cpp-Raytracer/Color.h
        cpp-Raytracer/Environment.cpp cpp-Raytracer/Environment.h
        cpp-Raytracer/Projectile.cpp cpp-Raytracer/Projectile.h
        cpp-Raytracer/Ray.cpp cpp-Raytracer/Ray.h
        cpp-Raytracer/Sphere.cpp cpp-Raytracer/Sphere.h
        cpp-Raytracer/Tracer.cpp cpp-Raytracer/Tracer.h cpp-Raytracer/Light.cpp cpp-Raytracer/Light.h cpp-Raytracer/Material.cpp cpp-Raytracer/Material.h)

add_subdirectory(Google_tests)