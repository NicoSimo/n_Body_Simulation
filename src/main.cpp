#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>

// Struct to store all the info about the single Body
struct Body {
    double mass;
    double x,y; // position
    double vx,vy; // velocity
    double ax,ay; // acceleration
};

// Function that computes forces acting on the bodies 
void computeForces(std::vector<Body>& bodies){

    const double G = 6.67430e-11; // Constant G
    for (size_t i = 0; i < bodies.size(); i++){
        bodies[i].ax = 0.0;
        bodies[i].ay = 0.0;
        for (size_t j = 0; j < bodies.size(); j++){
            if (i != j){
                double dx = bodies[j].x - bodies[i].x;
                double dy = bodies[j].y - bodies[i].y; 
                double distance = std::sqrt(dx*dx + dy*dy);
                // handling bodies that are really far from each other
                if (distance > 1e-5){
                    double force = G * bodies[i].mass * bodies[j].mass / (distance * distance);
                    bodies[i].ax += force * dx / (distance * bodies[i].mass);
                    bodies[i].ay += force * dy / (distance * bodies[i].mass);  
                }
            }
        }
    }
}

// Function that updates the bodies positions and velocities
void updatebodies(std::vector<Body>& bodies, double dt){

    for (auto& b : bodies){
        b.vx += b.ax * dt;
        b.vy += b.ay * dt;
        b.x += b.vx * dt;
        b.y += b.vy * dt;   
    }
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
    std::uniform_real_distribution<> massDist(1.0, 10.0); // Mass range [1.0, 10.0]
    std::uniform_real_distribution<> posDist(-100.0, 100.0); // Position range [-100.0, 100.0]
    std::uniform_real_distribution<> velDist(-10.0, 10.0); // Velocity range [-10.0, 10.0]
    std::uniform_real_distribution<> accDist(-0.1, 0.1);

    std::vector<Body> bodies(nBodies);    
    for (int i = 0; i < nBodies; ++i){
        bodies[i] = {
            massDist(gen), // Random mass
            posDist(gen), posDist(gen), // Random initial position (x, y)
            velDist(gen), velDist(gen), // Random initial velocity (vx, vy)
            accDist(gen), accDist(gen)  // Random initial acceleration (ax, ay)
        };
    }

    double dt = 0.01; 
    for (int i = 0; i < 1000; i++){
        computeForces(bodies);
        updatebodies(bodies, dt);

        std::cout << "Iteration " << i << ":\n";
        for(const auto& b : bodies){
            std::cout << "Body at (" << b.x << ", " << b.y << ")\n";
        }
        std::cout << "\n";
    }
    return 0;
}