#include <iostream>
#include <tngin/platform/game.h>
#include <tngin/service_locator.h>

#include <tngin/input/input_manager.h>

#include "platform_window.h"
#include "rendering/Graphics/tngin_graphics.h"
#include "rendering/Graphics/tngin_camera.h"

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
            .width = 1920,
            .height = 1080
        });

        // Initialize camera
        ServiceLocator::Provide(new TNGINCamera());

        // Initialize input system
        ServiceLocator::Provide(new InputManager());

        // Initialize renderer
        ServiceLocator::Provide(new TNGINGraphics());
    }

    void Game::shutdownServices() {
        std::cout << "Shutting down Services!" << std::endl;

        ServiceLocator::shutdownServices();
    }
}