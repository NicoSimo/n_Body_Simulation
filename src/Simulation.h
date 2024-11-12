#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#include "Body.h"
#include "Physics.h"
#include "Algorithm.h"

class Simulation
{
    std::unique_ptr<Algorithm> alg;
    int nBodies;
    void Simulate();

public:
    std::vector<std::shared_ptr<Body>> bodies;
    Simulation(int n);
    void update();
};