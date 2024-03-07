#pragma once

#include <tngin/platform/window.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace TAL {
    class PlatformWindow : public Window {
        public:
            PlatformWindow();
            void OpenWindow(WindowData data) override;
            bool Update() override;
            float GetAspectRatio() const override;

            static void error_callback(int error, const char* description);
            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        private:
            GLFWwindow* _window;
    };
}