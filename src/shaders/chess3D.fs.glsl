#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 uColorOverride;
uniform bool uUseOverride;

uniform sampler2D uTexture;
uniform bool uHasTexture;
uniform float uOpacity;

void main() {
    vec3 baseColor = uUseOverride ? uColorOverride : vec3(0.8);
    
    if (uHasTexture) {
        baseColor = texture(uTexture, TexCoords).rgb * baseColor;
    }
    
    // Ambient
    vec3 ambient = 0.4 * baseColor;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3)); // Simple direction
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * 0.7 * baseColor;
    
    vec3 result = ambient + diffuse;
    FragColor = vec4(result, uOpacity);
}
