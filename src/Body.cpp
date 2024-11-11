#include <glm/glm.hpp>

#include "Body.h"

Body::Body(){
    this->position = glm::vec2(0.0f, 0.0f);
    this->velocity = glm::vec2(0.0f, 0.0f);
    this->acceleration = glm::vec2(0.0f, 0.0f);
    this->mass = 1.0f;
}

Body::Body(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float mass){
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->mass = mass;
}