#version 400

in vec2 TexCoord0;

out vec4 frag_colour;

uniform sampler2D gSampler;

void main() {
    frag_colour = texture(gSampler, TexCoord0);
}