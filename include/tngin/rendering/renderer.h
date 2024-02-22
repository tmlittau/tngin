#pragma once

#include <string>

namespace TAL {
    struct RendererSettings {
        std::string app_name;
    };
    class Renderer {
        public:
            virtual void Init(RendererSettings) = 0;
            virtual void Shutdown() = 0;
            virtual void RenderFrame() = 0;
    };
}