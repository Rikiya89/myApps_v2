#version 150

in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2D uTexture;

void main() {
    vec4 color = texture(uTexture, vTexCoord);
    vec4 glow = vec4(color.rgb * 1.2, color.a);
    fragColor = glow;
}
