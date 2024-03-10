#pragma once

#include <memory>
#include <tngin/platform/window.h>
#include <tngin/rendering/graphic_engine.h>
#include <tngin/rendering/camera.h>
#include <tngin/input/input_manager.h>

namespace TAL {
    class ServiceLocator {
        public:
            static inline const std::unique_ptr<Window>& GetWindow() { return _window; };
            static inline GraphicsEngine* GetGraphicsEngine() { return _graphics_engine.get(); };
            static inline Camera* GetCamera() { return _camera.get(); };
            static inline InputManager* GetInputManager() { return _input_manager.get(); };

            static inline void Provide(Window* window) {
                if (_window != nullptr) return;
                _window = std::unique_ptr<Window>(window);
            }

            static inline void Provide(GraphicsEngine* graphics_engine) {
                if (_graphics_engine != nullptr) return;
                
                _graphics_engine = std::unique_ptr<GraphicsEngine>(graphics_engine);
                _graphics_engine->Init();
            }

            static inline void Provide(Camera* camera) {
                if (_camera != nullptr) return;
                
                _camera = std::unique_ptr<Camera>(camera);
                _camera->Init();
            }

            static inline void Provide(InputManager* input_manager) {
                if (_input_manager != nullptr) return;

                _input_manager = std::unique_ptr<InputManager>(input_manager);
                _input_manager->Init();
            }

            static inline void shutdownServices() {
                ShutdownWindow();
                ShutdownGraphicsEngine();
            }
        private:
            static inline std::unique_ptr<Window> _window = nullptr;
            static inline std::unique_ptr<GraphicsEngine> _graphics_engine = nullptr;
            static inline std::unique_ptr<Camera> _camera = nullptr;
            static inline std::unique_ptr<InputManager> _input_manager = nullptr;

            static inline void ShutdownWindow() {
                _window.reset();
                _window = nullptr;
            }

            static inline void ShutdownGraphicsEngine() {
                if (!_graphics_engine) return;

                _graphics_engine->Shutdown();
                _graphics_engine = nullptr;
            }
    };
}