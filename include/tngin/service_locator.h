#pragma once

#include <memory>
#include <tngin/platform/window.h>
#include <tngin/rendering/graphic_engine.h>

namespace TAL {
    class ServiceLocator {
        public:
            static inline const std::unique_ptr<Window>& GetWindow() { return _window; };
            static inline GraphicsEngine* GetGraphicsEngine() { return _graphics_engine.get(); };

            static inline void Provide(Window* window) {
                if (_window != nullptr) return;
                _window = std::unique_ptr<Window>(window);
            }

            static inline void Provide(GraphicsEngine* graphics_engine) {
                if (_graphics_engine != nullptr) return;
                
                _graphics_engine = std::unique_ptr<GraphicsEngine>(graphics_engine);
                _graphics_engine->Init();
            }

            static inline void shutdownServices() {
                ShutdownWindow();
            }
        private:
            static inline std::unique_ptr<Window> _window = nullptr;
            static inline std::unique_ptr<GraphicsEngine> _graphics_engine = nullptr;

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