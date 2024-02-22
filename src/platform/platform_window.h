#pragma once
#define GLFW_INCLUDE_VULKAN

#include <tngin/platform/window.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace TAL {
    class PlatformWindow : public Window {
        public:
            PlatformWindow();
            void OpenWindow(WindowData data) override;
            bool Update() override;
        private:
            GLFWwindow* _window;
    };
}