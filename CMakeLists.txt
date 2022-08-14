cmake_minimum_required(VERSION 3.21)
project(cpp_Raytracer)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")
set(CMAKE_CXX_STANDARD 20)

    add_executable(cpp_Raytracer cpp-Raytracer/main.cpp
        cpp-Raytracer/Math.cpp cpp-Raytracer/Math.h
            cpp-Raytracer/Canvas.cpp cpp-Raytracer/Canvas.h
            cpp-Raytracer/Color.cpp cpp-Raytracer/Color.h
            cpp-Raytracer/Ray.cpp cpp-Raytracer/Ray.h
            cpp-Raytracer/Shapes/Sphere.cpp cpp-Raytracer/Shapes/Sphere.h
        cpp-Raytracer/Light.cpp cpp-Raytracer/Light.h
            cpp-Raytracer/Material.cpp cpp-Raytracer/Material.h
            cpp-Raytracer/World.cpp cpp-Raytracer/World.h
            cpp-Raytracer/Intersection.cpp cpp-Raytracer/Intersection.h
            cpp-Raytracer/IntersectionComputations.h
            cpp-Raytracer/Camera.cpp cpp-Raytracer/Camera.h
            cpp-Raytracer/Shapes/Shape.cpp cpp-Raytracer/Shapes/Shape.h
            cpp-Raytracer/Shapes/Plane.cpp cpp-Raytracer/Shapes/Plane.h
            cpp-Raytracer/IntersectionComputations.cpp
            cpp-Raytracer/Pattern.cpp cpp-Raytracer/Pattern.h 
            cpp-Raytracer/Shapes/Cube.cpp cpp-Raytracer/Shapes/Cube.h 
            cpp-Raytracer/Shapes/Cylinder.h cpp-Raytracer/Shapes/Cylinder.cpp 
            cpp-Raytracer/Shapes/Cone.h cpp-Raytracer/Shapes/Cone.cpp)

add_subdirectory(Google_tests)