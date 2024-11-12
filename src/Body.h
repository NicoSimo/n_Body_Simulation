#pragma once
#include <iostream>
#include <glm/glm.hpp>

class Body
{
public:
    bool isDynamic;
    float mass;
    float radius;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    Body(float m, float r, glm::vec2 p, glm::vec2 v, glm::vec2 a, bool d = true) : mass(m), radius(r), position(p), velocity(v), acceleration(a), isDynamic(d) {}
    friend std::ostream &operator<<(std::ostream &os, const Body &b);
};