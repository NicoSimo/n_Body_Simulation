cmake_minimum_required(VERSION 3.10)
project(NBodySimulation)

set(CMAKE_CXX_STANDARD 17)

include_directories("/opt/homebrew/opt/glm/include")

add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(glfw3 3.3 REQUIRED)

find_library(COCOA_LIBRARY Cocoa)
find_library(OPENGL_LIBRARY OpenGL)

include_directories(${GLFW_INCLUDE_DIRS})

add_executable(nbody 
    ../src/main.cpp
    ../src/Body.cpp
    ../src/algorithm.cpp
    ../src/Simulation.cpp
    ../src/Physics.cpp
)

target_link_libraries(nbody glfw ${OPENGL_LIBRARY} ${COCOA_LIBRARY})