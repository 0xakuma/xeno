#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    float heightScale;
    float time;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;

// Simple noise function for terrain height
float noise(vec2 p) {
    return sin(p.x * 0.1) * cos(p.y * 0.1) * 0.5 + 
           sin(p.x * 0.05) * cos(p.y * 0.05) * 0.3 +
           sin(p.x * 0.02) * cos(p.y * 0.02) * 0.2;
}

vec3 calculateNormal(vec2 pos) {
    float eps = 0.1;
    float hL = noise(pos - vec2(eps, 0.0));
    float hR = noise(pos + vec2(eps, 0.0));
    float hD = noise(pos - vec2(0.0, eps));
    float hU = noise(pos + vec2(0.0, eps));
    
    vec3 normal = normalize(vec3(hL - hR, 2.0 * eps, hD - hU));
    return normal;
}

void main() {
    vec3 pos = inPosition;
    
    // Generate terrain height based on position
    float height = noise(pos.xz) * ubo.heightScale;
    pos.y += height;
    
    // Calculate normal for lighting
    fragNormal = calculateNormal(pos.xz);
    
    fragPos = vec3(ubo.model * vec4(pos, 1.0));
    fragTexCoord = inTexCoord;
    
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(pos, 1.0);
}
