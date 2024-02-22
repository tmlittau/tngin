#pragma once

#include <memory>
#include <tngin/platform/window.h>
#include <tngin/rendering/renderer.h>

namespace TAL {
    class ServiceLocator {
        public:
            static inline const std::unique_ptr<Window>& GetWindow() { return _window; };

            static inline const std::unique_ptr<Renderer>& GetRenderer() { return _renderer; };

            static inline void Provide(Window* window) {
                if (_window != nullptr) return;
                _window = std::unique_ptr<Window>(window);
            }

            static inline void Provide(Renderer* renderer, RendererSettings settings) {
                if (_renderer != nullptr) return;

                _renderer = std::unique_ptr<Renderer>(renderer);
                _renderer->Init(settings);
            }

            static inline void shutdownServices() {
                shutdownWindow();
            }
        private:
            static inline std::unique_ptr<Window> _window = nullptr;
            static inline std::unique_ptr<Renderer> _renderer = nullptr;

            static inline void shutdownWindow() {
                _window.reset();
                _window = nullptr;
            }
    };
}