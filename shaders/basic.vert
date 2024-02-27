#version 400

in vec3 vp;

uniform float gScale;

void main() {
    gl_Position = vec4(gScale * vp.x, gScale * vp.y, vp.z, 1.0);
}