#include "ogl_renderer.h"
#include <OpenGL/gltypes.h>
#include <OpenGL/gl.h>

namespace TAL {
    void OGLRenderer::Init() {
        // Initialize OpenGL
    }

    void OGLRenderer::Shutdown() {
        // Shutdown OpenGL
    }

    void OGLRenderer::RenderFrame() {
        // Render a frame using OpenGL
        static GLclampf red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
        glClearColor(red, green, blue, alpha);
        if (red < 1.0f) red += 0.01f;
        else if (green < 1.0f) green += 0.01f;
        else if (blue < 1.0f) blue += 0.01f;
        else {
            red = 0.0f;
            green = 0.0f;
            blue = 0.0f;
            alpha = 1.0f;
        }

        glClear(GL_COLOR_BUFFER_BIT);
    }
}