#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>

int main(){

    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    };

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if(glewInit()!=GLEW_OK){
        std::cout << "Error!" << std::endl;
    }

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}