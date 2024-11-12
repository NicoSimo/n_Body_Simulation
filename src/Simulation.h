#pragma once
#include <vector>
#include <memory>
#include "vector.h"
#include "Body.h"
#include "algorithm.h"

class Simulation
{
    std::unique_ptr<Algorithm> alg;
    int nBodies;
    void Simulate();

public:
    std::vector<std::shared_ptr<Body>> bodies;
    Simulation(int n, int a);
    void update();
};
