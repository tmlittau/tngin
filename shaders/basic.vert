#version 400

layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 TexCoord;

uniform mat4 gWorld;

out vec2 TexCoord0;

void main() {
    gl_Position = gWorld * vec4(vp, 1.0);
    TexCoord0 = TexCoord;
}