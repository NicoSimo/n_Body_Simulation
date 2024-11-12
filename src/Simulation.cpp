#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Simulation.h"
#include "Physics.h"
#include "constants.h"

Simulation::Simulation(int n, int a) : nBodies(n) {
    Simulate();
    alg = std::make_unique<Physics>(bodies);
}

void Simulation::Simulate() {
    srand(time(NULL));

    bodies.clear();
    float maxDistance = MAX_DIST;
    float minDistance = MIN_DIST;
    glm::vec3 centerPos(CENTERX, CENTERY, CENTERZ);
    for (int i = 0; i < nBodies - 1; ++i) {
        float angle = 2 * M_PI * (rand() / (float)RAND_MAX);
        float zAngle = M_PI * (rand() / (float)RAND_MAX) - (M_PI / 2); // Random angle for z-axis

        // Generate random distance from center within the given max distance
        float radius = (maxDistance - minDistance) * (rand() / (float)RAND_MAX) + minDistance;

        // Calculate coordinates of the point
        float x = centerPos.x + radius * std::cos(angle) * std::cos(zAngle);
        float y = centerPos.y + radius * std::sin(angle) * std::cos(zAngle);
        float z = centerPos.z + radius * std::sin(zAngle);

        glm::vec3 position(x, y, z);
        float distance = glm::distance(position, centerPos);
        glm::vec3 r = position - centerPos;
        glm::vec3 a = r / distance;

        // Calculate velocity glm::vec3 components
        float esc = sqrt((GRAVITY * SUN_MASS) / distance);
        glm::vec3 velocity(-a.y * esc, a.x * esc, a.z * esc);

        bodies.push_back(std::make_shared<Body>(EARTH_MASS, EARTH_DIA, position, velocity, glm::vec3(0, 0, 0)));
    }
    bodies.push_back(std::make_shared<Body>(SUN_MASS, SUN_DIA, centerPos, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), false));
}

void Simulation::update() {
    alg->update();
}