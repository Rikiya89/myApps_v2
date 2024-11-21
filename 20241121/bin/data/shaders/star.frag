#version 150

out vec4 outputColor;

uniform float u_time; // Time for animation

void main() {
    vec2 st = gl_FragCoord.xy / vec2(1920.0, 1080.0); // Normalize coordinates
    float dist = length(st - vec2(0.5)); // Distance from center

    // Glow effect based on distance from center
    float intensity = exp(-dist * 10.0) * 0.5 + 0.5;
    vec3 color = vec3(1.0, 0.4, 0.8) * intensity;

    outputColor = vec4(color, 1.0);
}
