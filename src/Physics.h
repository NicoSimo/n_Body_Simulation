#pragma once
#include <vector>
#include <memory>
#include "body.h"
#include "constants.h"
#include "algorithm.h"

class Physics : public Algorithm
{
    const double epsilon = 0.5;
    const double dt = 25000.0;

    void calculateAcceleration();
    void calculateVelocity();
    void calculatePosition();
    bool isCollide(Body b1, Body b2);

public:
    Physics(std::vector<std::shared_ptr<Body>> &bs);
    void update() override;
};