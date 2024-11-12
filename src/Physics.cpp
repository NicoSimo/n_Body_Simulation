#include <algorithm>
#include <math.h>
#include "Physics.h"
#include "constants.h"

Physics::Physics(std::vector<std::shared_ptr<Body>> &bs) : Algorithm(bs, bs.size()) {}

void Physics::calculateAcceleration()
{
    for (int i = 0; i < nBodies; ++i)
    {
        Body &bi = *bodies[i];
        bi.acceleration = Vector(0, 0);
        Vector force(0, 0);
        for (int j = 0; j < nBodies; ++j)
        {
            Body &bj = *bodies[j];
            if (i != j && bi.isDynamic && !isCollide(bi, bj))
            {

                Vector rij = bj.position - bi.position;
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
    float boundaryWidth = NBODY_WIDTH, boundaryHeight = NBODY_HEIGHT;

    // check if body is at boundary
    for (auto &body : bodies)
    {
        body->position += body->velocity * dt;
    }
}

bool Physics::isCollide(Body b1, Body b2)
{
    return b1.radius + b2.radius + COLLISION_TH >= b1.position.getDistance(b2.position);
}

void Physics::update()
{
    calculateAcceleration();
    calculateVelocity();
    calculatePosition();
}