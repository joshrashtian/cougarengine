//
// Created by Joshua Rashtian on 10/5/25.
//

#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class OpenGLWindow {
public:
    OpenGLWindow(int width, int height, const char* title);
    ~OpenGLWindow();
    void PollEvents() const;
    void SwapBuffers() const;
    bool ShouldClose() const;


private:
    GLFWwindow* window;

};



#endif //OPENGLWINDOW_H
