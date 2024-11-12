#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Body.h"
#include "Physics.h"

class Simulation
{
    int nBodies;
    void Simulate();
    Physics physics;

public:
    std::vector<std::shared_ptr<Body>> bodies;
    Simulation(int n);
    void updateForces();
};