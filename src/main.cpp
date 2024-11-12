     #include <iostream>
     #include <stdio.h>
     #include <stdlib.h>
     #include <math.h>
     #include <chrono>
     #include <GLFW/glfw3.h>
     #include "Simulation.h"
     #include "Physics.h"
     #include "constants.h"
     #include <stdexcept>

     void NotImplemented() {
          throw std::logic_error("Function not yet implemented");
     }

     glm::vec3 scaleToWindow3D(glm::vec3 pos){
          float scaleX = WINDOW_HEIGHT / NBODY_HEIGHT;
          float scaleY = WINDOW_WIDTH / NBODY_WIDTH;
          float scaleZ = WINDOW_DEPTH / NBODY_DEPTH;
          return glm::vec3((pos.x - 0) * scaleX + WINDOW_WIDTH / 2, 
                              (pos.y - 0) * scaleY + WINDOW_HEIGHT / 2,
                              (pos.z - 0) * scaleZ + WINDOW_DEPTH / 2);
     }

     glm::vec2 scaleToWindow2D(glm::vec2 pos){
          float scaleX = WINDOW_HEIGHT / NBODY_HEIGHT;
          float scaleY = WINDOW_WIDTH / NBODY_WIDTH;
          return glm::vec2((pos.x - 0) * scaleX + WINDOW_WIDTH / 2, 
                           (pos.y - 0) * scaleY + WINDOW_HEIGHT / 2);
     }

     void drawDots3D(Simulation &s){

          glColor3f(1.0, 1.0, 1.0); // set drawing color to white

          for (auto &body : s.bodies)
          {
               glPointSize(5);     // set point size to 5 pixels
               glBegin(GL_POINTS); // start drawing points
               glm::vec3 pos = scaleToWindow3D(body->position);
               glVertex3f(pos.x, pos.y, pos.z);
               glEnd(); // end drawing points
          }
     }

     void drawDots2D(Simulation &s){
          glColor3f(1.0, 1.0, 1.0); // set drawing color to white

          for (auto &body : s.bodies)
          {
               glPointSize(5);     // set point size to 5 pixels
               glBegin(GL_POINTS); // start drawing points
               glm::vec2 pos = scaleToWindow2D(glm::vec2(body->position.x, body->position.y));
               glVertex2f(pos.x, pos.y);
               glEnd(); // end drawing points
          }
     }

     int main(int argc, char **argv){
     if (argc != 3)
     {
          std::cerr << "Usage: " << argv[0] << " <number_of_bodies> <2d_or_3d>" << std::endl;
          return 1;
     }

     int nBodies = std::atoi(argv[1]);
     if (nBodies <= 0)
     {
          std::cerr << "Error, number of bodies must be a positive integer" << std::endl;
          return 1;
     }

     bool is3D = std::string(argv[2]) == "3d";

     Simulation s(nBodies, 0);

     // initialize GLFW
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
     if (is3D) {     
          NotImplemented();
          glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -WINDOW_DEPTH, WINDOW_DEPTH);
     } else {
          glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
     }

     while (!glfwWindowShouldClose(window)) // main loop
     {
          glClear(GL_COLOR_BUFFER_BIT); // clear the screen
          s.update();
          if (is3D) {
               drawDots3D(s);
          } else {
               drawDots2D(s);
          }
          glfwSwapBuffers(window); // swap front and back buffers
          glfwPollEvents();        // poll for events
     }

     glfwTerminate(); // terminate GLFW

     return 0;
     }