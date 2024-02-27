#include <iostream>
#include <tngin/platform/game.h>
#include <tngin/service_locator.h>

#include "platform_window.h"
#include "rendering/Graphics/tngin_graphics.h"

namespace TAL {
    Game::Game() : Game("TNGIN Game") {}

    Game::Game(std::string windowTitle) : _windowTitle(std::move(windowTitle)), _running(true) {
        initializeServices();
    }

    Game::~Game() {
        shutdownServices();
    }

    void Game::Run() {
        std::cout << "Running Game!" << std::endl;
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
            ServiceLocator::GetGraphicsEngine()->RenderFrame();
        }
    }

    void Game::initializeServices() {
        std::cout << "Initializing Services!" << std::endl;

        // Provide a window    
        ServiceLocator::Provide(new PlatformWindow());

        // Open the Window
        ServiceLocator::GetWindow()->OpenWindow({
            .title = _windowTitle,
            .width = 1080,
            .height = 1080
        });

        // Initialize input system

        // Initialize renderer
        ServiceLocator::Provide(new TNGINGraphics());
    }

    void Game::shutdownServices() {
        std::cout << "Shutting down Services!" << std::endl;

        ServiceLocator::shutdownServices();
    }
}