#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Body.h"

class Simulation
{
    int nBodies;
    void Simulate();

public:
    std::vector<std::shared_ptr<Body>> bodies;
    Simulation(int n);
    void updateForces();
};