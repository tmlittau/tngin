#include "platform_window.h"

namespace TAL {
    PlatformWindow::PlatformWindow() {
        _window = nullptr;
    }

    void PlatformWindow::OpenWindow(WindowData data) {
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        

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

        GLenum err = glewInit();

        if (GLEW_OK != err) {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }

    }

    bool PlatformWindow::Update() {
        glfwPollEvents();

        glfwSwapBuffers(_window);
        
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