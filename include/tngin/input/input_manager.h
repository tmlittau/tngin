#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace TAL {
    class InputManager {
        public:
            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
            
            void Init();

        private:
            static double _lastX;
            static double _lastY;
    };
}