#pragma once

#include <tngin/rendering/graphic_engine.h>
#include <tngin/platform/game.h>

#include <raylib.h>

namespace TAL {
    class TNGINGraphics : public GraphicsEngine {
        // OGL objects should have access to the renderer, so they are added as friends

        public:
            void Init() override;
            void Shutdown() override;
            void RenderFrame() override;

        private:

        public:
            
        private:

    };
}