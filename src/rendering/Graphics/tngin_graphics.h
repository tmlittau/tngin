#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <OpenGL/gltypes.h>
#include <OpenGL/gl.h>

#include <tngin/rendering/graphic_engine.h>
#include <tngin/rendering/graphics_types.h>
#include <tngin/rendering/graphics_transforms.h>
#include <tngin/rendering/texture.h>

#include "tngin_camera.h"

namespace TAL {
    class TNGINGraphics : public GraphicsEngine {
        public:
            void Init() override;
            void Shutdown() override;
            void RenderFrame() override;

            void BindCubeVAO() override;
            void BindPyramidVAO() override;
        private:
            void CreateShaders(const char* pVSFileName, const char* pFSFileName);
            GLuint AddShader(const char* pShaderText, GLenum ShaderType);

            void CreateCubeVAO();
            void CreatePyramidVAO();
        private:
            GLuint _shader_programme;
            GLint _gWorld;

            WorldTransform _w_transform;
            PersProjInfo _p_info;

            GLuint _cube_VBO;
            GLuint _cube_VAO;
            GLuint _cube_IBO;

            GLuint _pyramid_VBO;
            GLuint _pyramid_VAO;
            GLuint _pyramid_IBO;

            GLuint _g_sampler_location;
            Texture* _p_texture = NULL;

    };
}