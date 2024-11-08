cmake_minimum_required(VERSION 3.10)
project(NBodySimulation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if (NOT GLFW_FOUND)
    message(FATAL_ERROR "GLFW not found. Please install GLFW (e.g., sudo apt-get install libglfw3-dev)")
endif()

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories("/opt/homebrew/opt/glm/include")

add_executable(nbody_simulation ../src/main.cpp)
target_compile_definitions(nbody_simulation PRIVATE GL_SILENCE_DEPRECATION)
target_link_libraries(nbody_simulation ${GLFW_LIBRARIES})

if (APPLE)
    target_link_libraries(nbody_simulation "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(nbody_simulation ${OPENGL_LIBRARIES})
endif()
