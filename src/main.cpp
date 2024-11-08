#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

// Struct to store all the info about the single Body
struct Body {
    double mass;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
};


// Function that computes forces acting on the bodies 
void computeForces(std::vector<Body>& bodies){
    const double G = 1; // Constant G

    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].acceleration = glm::vec2(0.0, 0.0);

        for (size_t j = 0; j < bodies.size(); j++){
            if (i != j){
                double distance = glm::length(bodies[j].position - bodies[i].position);
                glm::vec2 direction = glm::normalize(bodies[j].position - bodies[i].position);
                double force = G * bodies[i].mass * bodies[j].mass / (distance * distance);
                bodies[i].acceleration += static_cast<float>(force / bodies[i].mass) * direction;
            }
        }
    }
}

// Function that updates the bodies positions and velocities
void updateBodies(std::vector<Body>& bodies, double dt) {
    for (auto& b : bodies) {
        b.velocity += b.acceleration * static_cast<float>(dt);
        b.position += b.velocity * static_cast<float>(dt);
    }
}

// Function to render bodies with OpenGL
void renderBodies(const std::vector<Body>& bodies){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto& b : bodies){
        float xNorm = static_cast<float>(b.position.x) / 100.0f;
        float yNorm = static_cast<float>(b.position.y) / 100.0f;
        glVertex2f(xNorm, yNorm);
    }
    glEnd();
}

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Usage: " << argv[0] << " number_of_bodies\n";
        return 1;
    }

    int nBodies = std::atoi(argv[1]);
    if (nBodies <= 0){
        std::cerr << "Error, number of bodies must be a positive integer \n";
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> massDist(100.0, 1000.0); // Mass range [1.0, 10.0]
    std::uniform_real_distribution<> posDist(-100.0, 100.0); // Position range [-100.0, 100.0]
    std::uniform_real_distribution<> velDist(-10.0, 10.0); // Velocity range [-10.0, 10.0]
    std::uniform_real_distribution<> accDist(-0.1, 0.1);

    std::vector<Body> bodies(nBodies);    
    for (int i = 0; i < nBodies; ++i){
        bodies[i] = {
            massDist(gen), // Random mass
            glm::vec2(posDist(gen), posDist(gen)), // Random initial position (x, y)
            glm::vec2(velDist(gen), velDist(gen)), // Random initial velocity (vx, vy)
            glm::vec2(accDist(gen), accDist(gen))  // Random initial acceleration (ax, ay)
        };
    }

    // checking glw initialization
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "N Body Simulation", nullptr, nullptr);
    if (!window){
        std::cerr << "Failed to create glfw window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glPointSize(15.0f);

    double dt = 0.005; 

    while (!glfwWindowShouldClose(window)){
        computeForces(bodies);
        updateBodies(bodies, dt);

        renderBodies(bodies);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}