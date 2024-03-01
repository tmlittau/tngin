#version 400

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 inColor;

uniform mat4 gWorld;

const vec4 colors[3] = vec4[3]( vec4(1, 0, 0, 1),
                                vec4(0, 1, 0, 1),
                                vec4(0, 0, 1, 1) );
out vec4 Color;

void main() {
    gl_Position = gWorld * vec4(vp, 1.0);
    Color = colors[gl_VertexID];
}