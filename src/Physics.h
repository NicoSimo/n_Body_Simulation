#pragma once
#include <vector>
#include <memory>
#include "Body.h"
#include "constants.h"
#include "algorithm.h"

class Physics : public Algorithm
{
    const float epsilon = 0.5;
    const float dt = 25000.0;

    void calculateAcceleration();
    void calculateVelocity();
    void calculatePosition();
    bool isCollide(Body b1, Body b2);

public:
    Physics(std::vector<std::shared_ptr<Body>> &bs);
    void update() override;
};