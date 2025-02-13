#version 150

in vec4 vColor;
out vec4 fragColor;

void main() {
    vec3 glow = vColor.rgb * 1.5; // Slight glow effect
    fragColor = vec4(glow, 1.0);
}