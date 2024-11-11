cmake_minimum_required(VERSION 3.10)
project(NBodySimulation)

set(CMAKE_CXX_STANDARD 11)

include_directories("/opt/homebrew/opt/glm/include")

add_executable(nbody 
    ../src/Main.cpp
    ../src/Body.cpp
    ../src/Physics.cpp
)