#version 150
uniform float u_time;
out vec4 outputColor;

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * vec2(1280, 720)) / 720.0;
    float color = 0.5 + 0.5 * cos(u_time + uv.xyx + vec3(0, 2, 4));
    outputColor = vec4(color, 1.0);
}
