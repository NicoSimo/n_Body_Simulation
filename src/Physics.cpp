#include <vector> 
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "Body.h"

void computeForces(std::vector<Body>& bodies){
    for(int i = 0; i < bodies.size(); ++i){
        glm::vec2 position1 = bodies[i].position;
        
        for(int j = 0; j < bodies.size(); ++j){
            if(i != j){
                glm::vec2 position2 = bodies[j].position;
                float m2 = bodies[j].mass;

                glm::vec2 r =  position2 - position1;
                float mag_sq = r.x * r.x + r.y * r.y;
                float mag = std::sqrt(mag_sq);
                
                glm::vec2 a1 = (m2 / (mag_sq * mag)) * r;
                bodies[i].acceleration += a1;
            }  
        }
    }
}

void updateBodies(std::vector<Body>& bodies, float dT){
    for (auto& body : bodies) {
        body.position += body.velocity * dT;
        body.velocity += body.acceleration * dT;
        body.acceleration = glm::vec2(0.0f, 0.0f); 
    }
}
