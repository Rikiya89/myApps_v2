#version 150

uniform vec3 lightPos;
uniform float time;

in vec3 fragColor;
out vec4 outputColor;

void main() {
    vec3 glowColor = fragColor * sin(time * 0.5) + vec3(0.2, 0.1, 0.8);
    float intensity = 1.0 / (distance(gl_FragCoord.xyz, lightPos) * 0.1);
    outputColor = vec4(glowColor * intensity, 1.0);
}
