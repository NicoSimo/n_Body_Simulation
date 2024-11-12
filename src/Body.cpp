#include "Body.h"

std::ostream& operator<<(std::ostream& os, const Body& b) {
    os << "Position: (" << b.position.x << ", " << b.position.y << ", " << b.position.z << "), "
       << "Velocity: (" << b.velocity.x << ", " << b.velocity.y << ", " << b.velocity.z << "), "
       << "Acceleration: (" << b.acceleration.x << ", " << b.acceleration.y << ", " << b.acceleration.z << "), "
       << "Mass: " << b.mass << ", "
       << "Radius: " << b.radius << ", ";
    return os;
}