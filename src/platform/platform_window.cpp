#include "platform_window.h"

namespace TAL {
    PlatformWindow::PlatformWindow() {
        _window = nullptr;
    }

    void PlatformWindow::OpenWindow(WindowData data) {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        _window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);

    }

    bool PlatformWindow::Update() {
        glfwPollEvents();
        
        return glfwWindowShouldClose(_window);
    }
}