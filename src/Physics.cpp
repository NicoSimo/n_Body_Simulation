#include <vector> 
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "Body.h"
#include "Physics.h"
#include "constants.h"  
#include "Simulation.h"

Physics::Physics(std::vector<std::shared_ptr<Body>> &bs, int n) : bodies(bs), nBodies(n) {}

void Physics::calculateAcceleration()
{
    for (int i = 0; i < nBodies; ++i)
    {
        Body &bi = *bodies[i];
        bi.acceleration = glm::vec2(0.0f, 0.0f);
        glm::vec2 force(0.0f, 0.0f);
        for (int j = 0; j < nBodies; ++j)
        {
            Body &bj = *bodies[j];
            if (i != j && bi.isDynamic && !isCollide(bi, bj))
            {
                glm::vec2 rij = bj.position - bi.position;
                float r = sqrt((rij.x * rij.x) + (rij.y * rij.y) + (epsilon * epsilon));
                float f = (GRAVITY * bi.mass * bj.mass) / (r * r * r + (epsilon * epsilon));
                force += rij * f;
            }
        }

        bi.acceleration += (force / bi.mass);
    }
}

void Physics::calculateVelocity()
{

    for (auto &body : bodies)
    {
        body->velocity += (body->acceleration * dt);
    }
}

void Physics::calculatePosition()
{
    double boundaryWidth = NBODY_WIDTH, boundaryHeight = NBODY_HEIGHT;

    // check if body is at boundary
    for (auto &body : bodies)
    {
        body->position += body->velocity * dt;
    }
}

void Physics::updateBodies(){
    calculateAcceleration();
    calculateVelocity();
    calculatePosition();
}
