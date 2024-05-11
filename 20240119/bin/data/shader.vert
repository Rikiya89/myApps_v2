#version 150
// This is a basic vertex shader

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
void main() {
    gl_Position = modelViewProjectionMatrix * position;
}
