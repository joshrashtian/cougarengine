#include "OpenGL/include/Window/OpenGLWindow.h"

int main()
{
    OpenGLWindow window(1280, 720, "Cougar Engine");

    while (!window.ShouldClose()) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffers();
        window.PollEvents();
    }
    return 0;
}
