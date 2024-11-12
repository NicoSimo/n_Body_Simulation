#include <vector> 
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "Body.h"
#include "Simulation.h"
#include "constants.h" 
#include "Physics.h" 

Simulation::Simulation(int n) : nBodies(n){
    Simulate();
    Physics physics(bodies, nBodies);
}

void Simulation::Simulate(){
    srand(time(NULL));

    bodies.clear();
    float maxDistance = MAX_DIST;
    float minDistance = MIN_DIST;
    glm::vec2 centerPos = glm::vec2(CENTERX, CENTERY);
    for (int i = 0; i < nBodies - 1; ++i){
        float angle = 2 * M_PI * (rand() / (float)RAND_MAX);

        float radius = (maxDistance - minDistance) * (rand() / (float)RAND_MAX) + minDistance;

        glm::vec2 position(
            centerPos.x + radius * std::cos(angle), 
            centerPos.y + radius * std::sin(angle)
        );

        float distance = glm::length(position - centerPos);
        glm::vec2 r = position - centerPos;
        glm::vec2 a = glm::normalize(r) / distance;

        float esc = std::sqrt(GRAVITY * SUN_MASS / distance);
        glm::vec2 velocity = glm::vec2(-a.y, a.x) * esc;

        bodies.push_back(std::make_shared<Body>(EARTH_MASS, EARTH_DIA, position, glm::vec2(0, 0), glm::vec2(0, 0)));
    }
    bodies.push_back(std::make_shared<Body>(SUN_MASS, SUN_DIA, centerPos, glm::vec2(0, 0), glm::vec2(0, 0), false));
}
