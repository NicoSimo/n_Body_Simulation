#pragma once

#include <vector>
#include "Body.h"

class Algorithm
{
protected:
    std::vector<std::shared_ptr<Body>> &bodies;
    int nBodies;

public:
    Algorithm(std::vector<std::shared_ptr<Body>> &bs, int n);
    virtual ~Algorithm() = default;
    virtual void update() = 0;
};
