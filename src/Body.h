#pragma once

#include <iostream>
#include <glm/glm.hpp>

class Body {
public :
    bool isDynamic;
    float mass;
    float radius;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    Body(float mass, float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration = glm::vec2(0.0f, 0.0f), bool d = true)
        : mass(mass), radius(radius), position(position), velocity(velocity), acceleration(acceleration), isDynamic(d){}
    friend std::ostream &operator<<(std::ostream &os, const Body &b);
};
