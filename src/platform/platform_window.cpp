#include "platform_window.h"

#include <iostream>

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

    void PlatformWindow::RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) {

        // Extract what we need
        try {
            auto vkInstance = std::any_cast<VkInstance>(args[SurfaceArgs::INSTANCE]);
            auto* allocationCallbacks = std::any_cast<VkAllocationCallbacks*>(args[SurfaceArgs::ALLOCATORS]);
            auto outSurface = std::any_cast<VkSurfaceKHR*>(args[SurfaceArgs::OUT_SURFACE]);

            if (glfwCreateWindowSurface(vkInstance, _window, allocationCallbacks, outSurface)!= VK_SUCCESS) {
                throw std::runtime_error("Failed to create window surface!");
            }
        } catch (std::bad_any_cast& e) {
            std::cout << "Failed to cast window surface arguments!" << e.what() << std::endl;
        }
    }
}