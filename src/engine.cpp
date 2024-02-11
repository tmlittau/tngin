#include <tngin/engine.h>
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <tngin/service_locator.h>

#include "platform/glfw_window.h"


void TNGIN::Init() {
    std::cout << "Initializing Window!" << std::endl;

    ServiceLocator::Provide(new CustomWindow());
}