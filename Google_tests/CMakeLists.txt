# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(cpp-Raytracer Math_tests.cpp Color_tests.cpp Raytracing_tests.cpp Scene_tests.cpp Shapes_tests.cpp Patterns_tests.cpp Reflections_tests.cpp Camera_tests.cpp Multithreading_tests.cpp Refractions_tests.cpp Random_tests.cpp)
target_link_libraries(cpp-Raytracer gtest gtest_main)