#include "platform_window.h"

PlatformWindow::PlatformWindow() {
    _window = nullptr;
}

void PlatformWindow::OpenWindow(WindowData data) {
    glfwInit();

    _window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);

}

bool PlatformWindow::Update() {
    glfwPollEvents();
    
    return glfwWindowShouldClose(_window);
}