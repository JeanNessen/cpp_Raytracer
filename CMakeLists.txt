cmake_minimum_required(VERSION 3.21)
project(cpp_Raytracer)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp")
set(CMAKE_CXX_STANDARD 20)

    add_executable(cpp_Raytracer cpp-Raytracer/main.cpp
        cpp-Raytracer/Math.cpp cpp-Raytracer/Math.h
            cpp-Raytracer/CCanvas.cpp cpp-Raytracer/CCanvas.h
            cpp-Raytracer/CColor.cpp cpp-Raytracer/CColor.h
            cpp-Raytracer/CRay.cpp cpp-Raytracer/CRay.h
            cpp-Raytracer/CSphere.cpp cpp-Raytracer/CSphere.h
        cpp-Raytracer/Light.cpp cpp-Raytracer/Light.h
            cpp-Raytracer/CMaterial.cpp cpp-Raytracer/CMaterial.h
            cpp-Raytracer/CWorld.cpp cpp-Raytracer/CWorld.h
            cpp-Raytracer/SIntersection.cpp cpp-Raytracer/SIntersection.h
            cpp-Raytracer/SIntersectionComputations.h
            cpp-Raytracer/CCamera.cpp cpp-Raytracer/CCamera.h
            cpp-Raytracer/CShape.cpp cpp-Raytracer/CShape.h
            cpp-Raytracer/CPlane.cpp cpp-Raytracer/CPlane.h
            cpp-Raytracer/SIntersectionComputations.cpp
            cpp-Raytracer/CPattern.cpp cpp-Raytracer/CPattern.h)

add_subdirectory(Google_tests)