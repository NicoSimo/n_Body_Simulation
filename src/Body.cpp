#include "Body.h"

#include "Body.h"

std::ostream& operator<<(std::ostream& os, const Body& b) {
    os << "Position: (" << b.position.x << ", " << b.position.y << "), "
       << "Velocity: (" << b.velocity.x << ", " << b.velocity.y << "), "
       << "Acceleration: (" << b.acceleration.x << ", " << b.acceleration.y << "), "
       << "Mass: " << b.mass << ", "
       << "Radius: " << b.radius << ", ";
    return os;
}