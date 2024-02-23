#pragma once

#include <tngin/rendering/renderer.h>

namespace TAL {
    class OGLRenderer : public Renderer {
        public:
            void Init() override;
            void Shutdown() override;
            void RenderFrame() override;
    };
}