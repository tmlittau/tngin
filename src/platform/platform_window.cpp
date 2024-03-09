#include "platform_window.h"

#include <tngin/service_locator.h>

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

        //glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    float PlatformWindow::GetWidth() const {
        int width, height;
        glfwGetFramebufferSize(_window, &width, &height);
        return (float)width;
    }

    float PlatformWindow::GetHeight() const {
        int width, height;
        glfwGetFramebufferSize(_window, &width, &height);
        return (float)height;
    }

    void PlatformWindow::error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    void PlatformWindow::SetKeyCallback()
    {
        glfwSetKeyCallback(_window, ServiceLocator::GetInputManager()->key_callback);
    }

    void PlatformWindow::SetCursorCallback()
    {
        glfwSetCursorPosCallback(_window, ServiceLocator::GetInputManager()->cursor_position_callback);
    }
}