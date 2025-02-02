#version 150

// Vertex attributes.
in vec4 position;
in vec3 normal;

// Outputs to the fragment shader.
out vec3 vNormal;
out vec3 vPosition;
out vec3 vViewDir;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main(){
    // Transform vertex position.
    gl_Position = modelViewProjectionMatrix * position;
    
    // Compute view-space position and normal.
    vPosition = vec3(modelViewMatrix * position);
    vNormal = normalize(normalMatrix * normal);
    
    // Calculate view direction (from vertex toward camera in view space).
    vViewDir = normalize(-vPosition);
}
