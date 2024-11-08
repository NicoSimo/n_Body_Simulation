#pragma once

#include <iostream>
#include <glm/glm.hpp>

class Body {
public :
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;

    Body();
    Body(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float mass);

    friend std::ostream& operator<<(std::ostream& os, const Body& b) {
        os << "Position: (" << b.position.x << ", " << b.position.y << "), "
            << "Velocity: (" << b.velocity.x << ", " << b.velocity.y << "), "
            << "Acceleration: (" << b.acceleration.x << ", " << b.acceleration.y << "), "
            << "Mass: " << b.mass;
        return os;
    }
};
