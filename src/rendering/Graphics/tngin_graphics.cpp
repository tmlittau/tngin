#include "tngin_graphics.h"

#include "graphics_types.h"
#include "graphics_utils.h"

#include <iostream>

namespace TAL {
    GLuint VBO;
    GLuint VAO;
    GLuint IBO;

    int vertex_count = 0;

    float scale = 1.0f;
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

        Matrix4f World(scale, 0.0f, 0.0f, 0.0f,
                        0.0f, scale, 0.0f, 0.0f,
                        0.0f, 0.0f, scale, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);

        glUniformMatrix4fv(_gWorld, 1, GL_TRUE, &World.m[0][0]);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertex_count);


    }

    void TNGINGraphics::CreateVertexBuffer() {
        // Create a vertex buffer for an object to be rendered
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CW);
        vertex_count = 19;

        Vertex vertices[vertex_count];

        // Center
        vertices[0] = Vertex(0.0f, 0.0);

        // Top row
        vertices[1] = Vertex(-1.0f,  1.0f);
        vertices[2] = Vertex(-0.75f, 1.0f);
        vertices[3] = Vertex(-0.50f, 1.0f);
        vertices[4] = Vertex(-0.25f, 1.0f);
        vertices[5] = Vertex(-0.0f,  1.0f);
        vertices[6] = Vertex(0.25f,  1.0f);
        vertices[7] = Vertex(0.50f,  1.0f);
        vertices[8] = Vertex(0.75f,  1.0f);
        vertices[9] = Vertex(1.0f,   1.0f);

        // Bottom row
        vertices[10] = Vertex(-1.0f,  -1.0f);
        vertices[11] = Vertex(-0.75f, -1.0f);
        vertices[12] = Vertex(-0.50f, -1.0f);
        vertices[13] = Vertex(-0.25f, -1.0f);
        vertices[14] = Vertex(-0.0f,  -1.0f);
        vertices[15] = Vertex(0.25f,  -1.0f);
        vertices[16] = Vertex(0.50f,  -1.0f);
        vertices[17] = Vertex(0.75f,  -1.0f);
        vertices[18] = Vertex(1.0f,   -1.0f);
        

        //BuildCircle(vertices, 1.0f, vertex_count);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        CreateIndexBuffer();

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        
    }

    void TNGINGraphics::CreateIndexBuffer() {
        // Create the corresponding Index Buffer to the Vertex Buffer
        unsigned int indices[] = { // Top triangles
                               0, 2, 1,
                               0, 3, 2,
                               0, 4, 3,
                               0, 5, 4,
                               0, 6, 5,
                               0, 7, 6,
                               0, 8, 7,
                               0, 9, 8,

                               // Bottom triangles
                               0, 10, 11,
                               0, 11, 12,
                               0, 12, 13,
                               0, 13, 14,
                               0, 14, 15,
                               0, 15, 16,
                               0, 16, 17,
                               0, 17, 18,

                               // Left triangle
                               0, 1, 10,

                               // Right triangle
                               0, 18, 9 };

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

}