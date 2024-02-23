#pragma once

#include <string>

namespace TAL {
    class Renderer {
        public:
            virtual void Init() = 0;
            virtual void Shutdown() = 0;
            virtual void RenderFrame() = 0;
    };
}