#pragma once

#include <tngin/platform/window.h>
#include <GLFW/glfw3.h>

class PlatformWindow : public Window {
    public:
        PlatformWindow();
        void OpenWindow(WindowData data) override;
        bool Update() override;
    private:
        GLFWwindow* _window;
};