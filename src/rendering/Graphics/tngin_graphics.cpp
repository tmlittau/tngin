#include "tngin_graphics.h"

#include <iostream>
#include <tngin/service_locator.h>

#include <tngin/rendering/graphics_types.h>
#include <tngin/rendering/graphics_utils.h>

namespace TAL {
    int vertex_count = 0;

    void TNGINGraphics::Init() {
        // Init Perspective Info
        float FOV = 45.0f;
        float zNear = 1.0f;
        float zFar = 100.0f;
        float ar = ServiceLocator::GetWindow()->GetWidth() / ServiceLocator::GetWindow()->GetHeight();

        _p_info = { FOV, ar, zNear, zFar };

        // Init OpenGL Settings
        glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);

        // Create Objects
        CreateCubeVAO();
        CreatePyramidVAO();

        glBindVertexArray(_cube_VAO);

        CreateShaders("shaders/basic.vert", "shaders/basic.frag");

        _p_texture = new Texture(GL_TEXTURE_2D, "textures/example.jpg");
        if (!_p_texture->Load()) {
            fprintf(stderr, "Error loading texture\n");
            exit(1);
        }

        _p_texture->Bind(GL_TEXTURE0);
        glUniform1i(_g_sampler_location, 0);
    }

    void TNGINGraphics::Shutdown() {
        // Shutdown OpenGL
        if (_p_texture) {
            delete _p_texture;
            _p_texture = NULL;
        }

        if (_cube_VAO != -1) {
            glDeleteVertexArrays(1, &_cube_VAO);
            _cube_VAO = -1;
        }
        if (_cube_VBO != -1) {
            glDeleteBuffers(1, &_cube_VBO);
            _cube_VBO = -1;
        }
        if (_cube_IBO != -1) {
            glDeleteBuffers(1, &_cube_IBO);
            _cube_IBO = -1;
        }

        if (_pyramid_VAO != -1) {
            glDeleteVertexArrays(1, &_pyramid_VAO);
            _pyramid_VAO = -1;
        }
        if (_pyramid_VBO != -1) {
            glDeleteBuffers(1, &_pyramid_VBO);
            _pyramid_VBO = -1;
        }
        if (_pyramid_IBO != -1) {
            glDeleteBuffers(1, &_pyramid_IBO);
            _pyramid_IBO = -1;
        }

        if (_shader_programme != -1) {
            glDeleteProgram(_shader_programme);
            _shader_programme = -1;
        }
    }

    void TNGINGraphics::RenderFrame() {
        // Render a frame using OpenGL
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(_shader_programme);

        float YRotationAngle = 1.0f;

        _w_transform.SetTranslation(0.0f, 0.0f, 5.0f);
        _w_transform.Rotate(0.0f, YRotationAngle, 0.0f);

        Matrix4f World = _w_transform.GetMatrix();

        Matrix4f View = ServiceLocator::GetCamera()->GetMatrix();

        Matrix4f Projection;
        Projection.InitPersProjTransform(_p_info);

        Matrix4f WVP = Projection * View * World;
        glUniformMatrix4fv(_gWorld, 1, GL_TRUE, &WVP.m[0][0]);

        GLint current_VAO;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current_VAO);

        if (current_VAO == _cube_VAO) {
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        } else {
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        }




    }

    void TNGINGraphics::CreateShaders(const char* pVSFileName, const char* pFSFileName)
    {   
        std::string vertex_shader, fragment_shader;

        if (!ReadFile(pVSFileName, vertex_shader)) {
            exit(1);
        };
        GLuint vs = AddShader(vertex_shader.c_str(), GL_VERTEX_SHADER);

        if (!ReadFile(pFSFileName, fragment_shader)) {
            exit(1);
        };
        GLuint fs = AddShader(fragment_shader.c_str(), GL_FRAGMENT_SHADER);

        _shader_programme = glCreateProgram();

        if (_shader_programme == 0) {
            fprintf(stderr, "Error creating shader program\n");
            exit(1);
        }

        glAttachShader(_shader_programme, fs);
        glAttachShader(_shader_programme, vs);
        glLinkProgram(_shader_programme);

        // link Uniform Location to property
        _gWorld = glGetUniformLocation(_shader_programme, "gWorld");

        if (_gWorld == -1) {
            fprintf(stderr, "Error finding 'gScale'\n");
            exit(1);
        }
    }

    GLuint TNGINGraphics::AddShader(const char* pShaderText, GLenum ShaderType)
    {  
        GLuint ShaderObj = glCreateShader(ShaderType);

        glShaderSource(ShaderObj, 1, &pShaderText, NULL);
        glCompileShader(ShaderObj);

        GLint success;
        glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
            exit(1);
        }

        return ShaderObj;
    }

    void TNGINGraphics::CreateCubeVAO() {
        glGenVertexArrays(1, &_cube_VAO);
        glBindVertexArray(_cube_VAO);

        Vertex vertices[8];

        // prepare Texture Vectors
        Vector2f t00(0.0f, 0.0f);
        Vector2f t01(0.0f, 1.0f);
        Vector2f t10(1.0f, 0.0f);
        Vector2f t11(1.0f, 1.0f);

        // Cube Vertices
        vertices[0] = Vertex(Vector3f(0.5f, 1.0f, 0.5f), t00);
        vertices[1] = Vertex(Vector3f(-0.5f,  1.0f, -0.5f), t01);
        vertices[2] = Vertex(Vector3f(-0.5f, 1.0f, 0.5f), t10);
        vertices[3] = Vertex(Vector3f(0.5f, 0.0f, -0.5f), t11);
        vertices[4] = Vertex(Vector3f(-0.5f, 0.0f, -0.5f), t00);
        vertices[5] = Vertex(Vector3f(0.5f,  1.0f, -0.5f), t10);
        vertices[6] = Vertex(Vector3f(0.5f,  0.0f, 0.5f), t01);
        vertices[7] = Vertex(Vector3f(-0.5f,  0.0f, 0.5f), t11);

        glGenBuffers(1, &_cube_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _cube_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Cube position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        // Cube texture
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

        // Cube Index Buffer
        unsigned int indices[] = { 
            0, 1, 2,
            1, 3, 4,
            5, 6, 3,
            7, 3, 6,
            2, 4, 7,
            0, 7, 6,
            0, 5, 1,
            1, 5, 3,
            5, 0, 6,
            7, 4, 3,
            2, 1, 4,
            0, 2, 7
        };

        glGenBuffers(1, &_cube_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cube_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void TNGINGraphics::CreatePyramidVAO() {
        glGenVertexArrays(1, &_pyramid_VAO);
        glBindVertexArray(_pyramid_VAO);

        Vertex vertices[4];

        // prepare Texture Vectors
        Vector2f t00(0.0f, 0.0f);
        Vector2f t050(0.5f, 1.0f);
        Vector2f t10(1.0f, 0.0f);
        Vector2f t051(0.5f, 1.0f);

        // Pyramid Vertices
        vertices[0] = Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), t00);
        vertices[1] = Vertex(Vector3f(0.0f,  -1.0f, -1.15475f), t050);
        vertices[2] = Vertex(Vector3f(1.0f, -1.0f, 0.5773f), t10);
        vertices[3] = Vertex(Vector3f(0.0f, 1.0f, 0.0f), t051);

        glGenBuffers(1, &_pyramid_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _pyramid_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Pyramid position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        // Pyramid texture
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

        // Pyramid Index Buffer
        unsigned int indices[] = { 
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
        };

        glGenBuffers(1, &_pyramid_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _pyramid_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void TNGINGraphics::BindCubeVAO() {
        glBindVertexArray(_cube_VAO);
    }

    void TNGINGraphics::BindPyramidVAO() {
        glBindVertexArray(_pyramid_VAO);
    }
}