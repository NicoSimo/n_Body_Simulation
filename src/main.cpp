#include <iostream>
#include <vector>
#include <cmath>

struct Particle {
    double mass;
    double x,y; // position
    double vx,vy; // velocity
    double ax,ay; // acceleration
};


void computeForces(std::vector<Partcile>& particles){
'''
    Function that computes forces acting on the particles 
'''
    const double G = 6.67430e-11; // Constant G
    for (size_t i = 0; i < particle.size(); i++){
        particle[i].ax = 0.0;
        particle[i].ay = 0.0;
        for (size_t j = 0; j < particle.size(); j++){
            if (i != j){
                double dx = particle[j].x - particle[i].x;
                double dy = particle[j].y - particle[i].y; 
                double distance = std::sqrt(dx*dx + dy*dy);
                // handling bodies that are really far from each other
                if (dist > 1e-5){
                    double force = G * particle[i].mass * particle[j].mass / (dist * dist);
                    particle[i].ax += force * dx / (dist * particle[i].mass);
                    particle[i].ay += force * dy / (dist * particle[i].mass);  
                }
            }
        }
    }
}

void updateParticle(std::vector<Particle>& particles, double dt){
'''
    Function that updates the particles positions and velocities
'''
    for 
}