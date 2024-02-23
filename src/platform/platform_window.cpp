#include "platform_window.h"

namespace TAL {
    PlatformWindow::PlatformWindow() {
        _window = nullptr;
    }

    void PlatformWindow::OpenWindow(WindowData data) {
        glfwInit();

        _window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);

        if(!_window) {
            glfwTerminate();
            return;
        }

        // set window current context
        glfwMakeContextCurrent(_window);

        // set glfw callbacks
        glfwSetErrorCallback(error_callback);
        glfwSetKeyCallback(_window, key_callback);

    }

    bool PlatformWindow::Update() {
        glfwSwapBuffers(_window);

        glfwPollEvents();
        
        return glfwWindowShouldClose(_window);
    }

    void PlatformWindow::error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    void PlatformWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}