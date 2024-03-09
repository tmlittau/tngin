#include <tngin/input/input_manager.h>

#include <tngin/service_locator.h>

#include <iostream>

namespace TAL {
    double InputManager::_lastX = 0;
    double InputManager::_lastY = 0;

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
        if ((key == GLFW_KEY_PAGE_UP) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(0.0f, 1.0f, 0.0f);
        if ((key == GLFW_KEY_PAGE_DOWN) && (action == GLFW_PRESS || action == GLFW_REPEAT))
            ServiceLocator::GetCamera()->Move(0.0f, -1.0f, 0.0f);
    }

    void InputManager::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        /*
        if (xpos < 0) xpos = 0;
        if (ypos < 0) ypos = 0;
        if (xpos > ServiceLocator::GetWindow()->GetWidth()) xpos = ServiceLocator::GetWindow()->GetWidth();
        if (ypos > ServiceLocator::GetWindow()->GetHeight()) ypos = ServiceLocator::GetWindow()->GetHeight();
        */

        float xoffset = xpos - _lastX;
        float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

        _lastX = xpos;
        _lastY = ypos;

        ServiceLocator::GetCamera()->Rotate(xoffset, yoffset);

    }

    void InputManager::Init() {
        _lastX = ServiceLocator::GetWindow()->GetWidth() / 2;
        _lastY = ServiceLocator::GetWindow()->GetHeight() / 2;

        ServiceLocator::GetWindow()->SetKeyCallback();
        ServiceLocator::GetWindow()->SetCursorCallback();
    }
}