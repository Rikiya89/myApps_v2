#version 150

// Inputs from the vertex shader.
in vec3 vNormal;
in vec3 vPosition;
in vec3 vViewDir;

uniform float u_time;
uniform vec3 u_lightPos;

out vec4 outputColor;

void main(){
    // Compute light direction.
    vec3 lightDir = normalize(u_lightPos - vPosition);
    
    // Diffuse lighting.
    float diff = max(dot(normalize(vNormal), lightDir), 0.0);
    
    // Fresnel term for a glowing rim effect.
    float fresnel = pow(1.0 - max(dot(normalize(vNormal), vViewDir), 0.0), 2.5);
    
    // Base color: soft shifting pastels.
    vec3 pastelA = vec3(0.8, 0.9, 1.0);
    vec3 pastelB = vec3(1.0, 0.8, 0.9);
    float mixFactor = 0.5 + 0.5 * sin(u_time * 0.3 + vPosition.y * 0.02);
    vec3 baseColor = mix(pastelA, pastelB, mixFactor);
    
    // Combine diffuse and Fresnel glow.
    vec3 color = baseColor * diff + vec3(1.0, 0.9, 1.0) * fresnel * 0.6;
    
    // Output with slight translucency.
    outputColor = vec4(color, 0.9);
}
