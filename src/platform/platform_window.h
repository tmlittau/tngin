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
            void SetKeyCallback() override;

            static void error_callback(int error, const char* description);
        private:
            GLFWwindow* _window;
    };
}