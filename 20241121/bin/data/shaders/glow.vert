#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 color;

out vec3 fragColor;

void main() {
    fragColor = color;
    gl_Position = modelViewProjectionMatrix * position;
}
