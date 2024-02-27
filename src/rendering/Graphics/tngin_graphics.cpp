#include "tngin_graphics.h"

#include "graphics_types.h"
#include "graphics_utils.h"

#include <iostream>

namespace TAL {
    GLuint VBO;
    GLuint VAO;
    int vertex_count = 500;

    float scale = 0.0f;
    float factor = 1.0f;

    void TNGINGraphics::Init() {
        // Initialize OpenGL
        CreateVertexBuffer();

        CreateShaders("shaders/basic.vert", "shaders/basic.frag");
    }

    void TNGINGraphics::Shutdown() {
        // Shutdown OpenGL
    }

    void TNGINGraphics::RenderFrame() {
        // Render a frame using OpenGL
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(_shader_programme);

        
        scale += factor*0.01f;
        if (scale > 1.0f || scale < 0.0f) factor *= -1.0f;
        

        glUniform1f(_gScaleLocation, scale);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertex_count*3);


    }

    void TNGINGraphics::CreateVertexBuffer() {
        // Create a vertex buffer with a triangle with vertices at (-1, -1, 0), (0, 1, 0) and (1, -1, 0)
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CW);
        
        std::vector<glm::vec3> vertices;

        BuildCircle(vertices, 1.0f, vertex_count);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        
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
        _gScaleLocation = glGetUniformLocation(_shader_programme, "gScale");

        if (_gScaleLocation == -1) {
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

}