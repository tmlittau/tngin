#pragma once

#include <string>
#include <any>
#include <unordered_map>

namespace TAL {
    enum class SurfaceArgs {
        INSTANCE,
        ALLOCATORS,
        OUT_SURFACE
    };
    struct WindowData {
        std::string title;
        int width, height;

    };

    class Window {
        public:
            virtual void OpenWindow(WindowData data) = 0;
            virtual bool Update() = 0;

            virtual void RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any>) = 0;

            virtual ~Window() = default;
    };
}