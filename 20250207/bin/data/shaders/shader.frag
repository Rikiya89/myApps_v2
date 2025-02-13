#version 150

out vec4 outputColor;
uniform float time;
uniform vec3 color1;
uniform vec3 color2;

void main() {
    float glow = sin(time * 0.5) * 0.5 + 0.5;
    vec3 finalColor = mix(color1, color2, glow);
    outputColor = vec4(finalColor, 0.9);
}
