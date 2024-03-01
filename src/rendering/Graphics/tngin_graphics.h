#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <OpenGL/gltypes.h>
#include <OpenGL/gl.h>

#include <tngin/rendering/graphic_engine.h>

namespace TAL {
    class TNGINGraphics : public GraphicsEngine {
        // OGL objects should have access to the renderer, so they are added as friends

        public:
            void Init() override;
            void Shutdown() override;
            void RenderFrame() override;

        private:
            void CreateVertexBuffer();
            void CreateIndexBuffer();
            void CreateShaders(const char* pVSFileName, const char* pFSFileName);
            GLuint AddShader(const char* pShaderText, GLenum ShaderType);

        public:

        private:
            GLuint _shader_programme;
            GLint _gWorld;
    };
}