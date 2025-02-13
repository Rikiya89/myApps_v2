#version 150

uniform float time;
in vec4 position;
out vec4 vColor;

void main() {
    float pulse = sin(position.x * 0.03 + time) * cos(position.y * 0.03 + time) * 0.1;
    vec4 newPos = position + vec4(position.xyz * pulse, 0.0);
    
    gl_Position = modelViewProjectionMatrix * newPos;

    float intensity = smoothstep(-1.0, 1.0, position.y);
    vColor = mix(vec4(1.0, 0.5, 1.0, 1.0), vec4(0.1, 0.8, 1.0, 1.0), intensity);
}
