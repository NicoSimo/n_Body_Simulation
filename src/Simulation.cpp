#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <glm/glm.hpp>
#include "Simulation.h"
#include "Physics.h"
#include "constants.h"

Simulation::Simulation(int n, int a) : nBodies(n){

    Simulate();
    alg = std::make_unique<Physics>(bodies);
}

void Simulation::Simulate()
{
    srand(time(NULL));

    bodies.clear();
    float maxDistance = MAX_DIST;
    float minDistance = MIN_DIST;
    glm::vec2 centerPos(CENTERX, CENTERY);
    for (int i = 0; i < nBodies - 1; ++i)
    {

        float angle = 2 * M_PI * (rand() / (float)RAND_MAX);
        // Generate random distance from center within the given max distance
        float radius = (maxDistance - minDistance) * (rand() / (float)RAND_MAX) + minDistance;

        // Calculate coordinates of the point
        float x = centerPos.x + radius * std::cos(angle);
        float y = centerPos.y + radius * std::sin(angle);

        glm::vec2 position(x, y);
        float distance = glm::distance(position, centerPos);
        glm::vec2 r = position - centerPos;
        glm::vec2 a = r / static_cast<float>(distance);

        // Calculate velocity glm::vec2 components
        float esc = sqrt((GRAVITY * SUN_MASS) / (distance));
        glm::vec2 velocity(-a.y * esc, a.x * esc);

        bodies.push_back(std::make_shared<Body>(EARTH_MASS, EARTH_DIA, position, velocity, glm::vec2(0, 0)));
    }

    bodies.push_back(std::make_shared<Body>(SUN_MASS, SUN_DIA, centerPos, glm::vec2(0, 0), glm::vec2(0, 0), false));
}

void Simulation::update()
{
    alg->update();
}