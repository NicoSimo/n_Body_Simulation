#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "Body.h"

void computeForces(std::vector<Body>& bodies);
void updateBodies(std::vector<Body>& bodies, float dT);
