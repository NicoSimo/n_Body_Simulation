#pragma once
#include <iostream>
#include <glm/glm.hpp>

class Body
{
public:
    bool isDynamic;
    float mass;
    float radius;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Body(float m, float r, glm::vec3 p, glm::vec3 v, glm::vec3 a, bool d = true) : mass(m), radius(r), position(p), velocity(v), acceleration(a), isDynamic(d) {}
    friend std::ostream &operator<<(std::ostream &os, const Body &b);
};