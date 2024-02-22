#include <iostream>
#include <tngin/platform/game.h>
#include <tngin/service_locator.h>

#include "platform_window.h"
#include "rendering/vulkan/vulkan_renderer.h"

namespace TAL {
    Game::Game() : Game("TNGIN Game") {}

    Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
        initializeServices();
    }

    Game::~Game() {
        shutdownServices();
    }

    void Game::Run() {
        std::cout << "Running Game!" << std::endl;

        // Open the Window
        ServiceLocator::GetWindow()->OpenWindow({
            .title = _title,
            .width = 800,
            .height = 600
        });

        // Game Loop
        while(_running) {
            // Update the window
            if(ServiceLocator::GetWindow()->Update()) {
                _running = false;
                continue;
            }

            // calculate deltaTime

            // Update game state
            Update(0.0f);

            // Update physics
            PhysicsUpdate(0.0f);

            // Draw
            ServiceLocator::GetRenderer()->RenderFrame();
        }
    }

    void Game::initializeServices() {
        std::cout << "Initializing Services!" << std::endl;

        // Provide a window    
        ServiceLocator::Provide(new PlatformWindow());

        // Initialize input system

        // Initialize renderer
        RendererSettings settings {
            .app_name = _title
        };

        ServiceLocator::Provide(new VulkanRenderer, settings);
    }

    void Game::shutdownServices() {
        std::cout << "Shutting down Services!" << std::endl;

        ServiceLocator::shutdownServices();
    }
}
