//
// Created by Joshua Rashtian on 10/5/25.
//

#include "../../include/Window/OpenGLWindow.h"
#include <iostream>

using namespace std;

OpenGLWindow::OpenGLWindow(int width, int height, const char* title) {
   if(!glfwInit()) {
       cerr << "Failed to initalize our GLFW.";
       return;
   }
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
   window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    std::cout << "✅ OpenGL window created successfully!" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    if ( window ) glfwDestroyWindow(window);
    glfwTerminate();
    cout << "Window has been closed!";
}

void OpenGLWindow::PollEvents() const {
    glfwPollEvents();
}

void OpenGLWindow::SwapBuffers() const {
    glfwSwapBuffers(window);
}

bool OpenGLWindow::ShouldClose() const {
    return glfwWindowShouldClose(window);
}




