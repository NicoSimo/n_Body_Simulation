#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Body.h"
#include "constants.h"
#include "Physics.h"
#include "Simulation.h"

glm::vec2 scaleToWindow(glm::vec2 pos)
{
    float scaleX = WINDOW_HEIGHT / NBODY_HEIGHT;
    float scaleY = WINDOW_WIDTH / NBODY_WIDTH;
    return glm::vec2(
        (pos.x * scaleX) + WINDOW_WIDTH / 2, 
        (pos.y * scaleY) + WINDOW_HEIGHT / 2
    );
}

void drawDots(Simulation &s)
{

    glColor3f(1.0, 1.0, 1.0); // set drawing color to white

    for (auto &body : s.bodies)
    {
        glPointSize(5);     // set point size to 5 pixels
        glBegin(GL_POINTS); // start drawing points
        glm::vec2 pos = scaleToWindow(body->position);
        glVertex2f(pos.x, pos.y);
        glEnd(); // end drawing points
    }
}

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

    Simulation s(nBodies);

    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "N-Body Simulation CPU", NULL, NULL); // create window
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // set context to current window

    glClearColor(0.0, 0.0, 0.0, 1.0); // set background color to black
    glMatrixMode(GL_PROJECTION);      // set up projection matrix
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) // main loop
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    
        s.updateForces();
        drawDots(s);
    
        glfwSwapBuffers(window); // swap front and back buffers
        glfwPollEvents();        // poll for events
    }

    glfwTerminate(); // terminate GLFW

    
    return 0;
}