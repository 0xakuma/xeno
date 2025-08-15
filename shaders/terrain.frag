#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    float heightScale;
    float time;
} ubo;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

void main() {
    // Simple lighting
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    vec3 normal = normalize(fragNormal);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Color based on height
    float height = fragPos.y;
    vec3 color;
    
    if (height < 0.0) {
        color = vec3(0.2, 0.4, 0.8); // Water blue
    } else if (height < 2.0) {
        color = vec3(0.9, 0.8, 0.6); // Sand
    } else if (height < 5.0) {
        color = vec3(0.3, 0.6, 0.2); // Grass
    } else if (height < 8.0) {
        color = vec3(0.4, 0.3, 0.2); // Rock
    } else {
        color = vec3(0.9, 0.9, 0.9); // Snow
    }
    
    // Apply lighting
    vec3 ambient = color * 0.3;
    vec3 diffuse = color * diff * 0.7;
    
    outColor = vec4(ambient + diffuse, 1.0);
}
