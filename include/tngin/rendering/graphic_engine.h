#pragma once

#include <string>

namespace TAL {
    class GraphicsEngine {
        public:
            virtual void Init() = 0;
            virtual void Shutdown() = 0;
            virtual void RenderFrame() = 0;

            virtual void BindCubeVAO() = 0;
            virtual void BindPyramidVAO() = 0;
    };
}