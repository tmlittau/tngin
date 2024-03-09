#include <tngin/input/input_manager.h>

#include <tngin/service_locator.h>

namespace TAL {
    void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        if ((key == GLFW_KEY_W || key == GLFW_KEY_UP) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(0.0f, 0.0f, 1.0f);
        if ((key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(0.0f, 0.0f, -1.0f);
        if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(-1.0f, 0.0f, 0.0f);
        if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(1.0f, 0.0f, 0.0f);
    }

    void InputManager::Init() {
        ServiceLocator::GetWindow()->SetKeyCallback();
    }
}