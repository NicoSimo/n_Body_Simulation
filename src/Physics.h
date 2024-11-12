#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Body.h"

class Physics
{
    const float epsilon = 0.5;
    const float dt = 25000.0;

    int nBodies;
    std::vector<std::shared_ptr<Body>> &bodies;

public:
    Physics(std::vector<std::shared_ptr<Body>> &bs, int n);
    void calculateAcceleration();
    void calculateVelocity();
    void calculatePosition();
    void updateBodies();
    bool isCollide(Body b1, Body b2);
};
