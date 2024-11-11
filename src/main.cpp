#include <iostream>
#include <glm/glm.hpp>

#include "Body.h"

int main(int argc, char* argv[]){

    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    int nBodies = std::atoi(argv[1]);
    if (nBodies <= 0){
        std::cerr << "Error, number of bodies must be a positive integer" << std::endl;
    }

    Body B[nBodies];

    for(int i = 0; i < nBodies; ++i){
        B[i]= Body(glm::vec2(0.0f, 0.0f), 
                   glm::vec2(0.0f, 0.0f), 
                   glm::vec2(0.0f, 0.0f), 
                   (1.0f + float(i)));
    }

    for(int i = 0; i < nBodies; ++i){
        std::cout << B[i] << std::endl;
    }
    
    return 0;
}