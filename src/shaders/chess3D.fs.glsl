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
uniform bool uIsWhiteTurn;

void main() {
    vec3 baseColor = uUseOverride ? uColorOverride : vec3(0.8);
    
    if (uHasTexture) {
        baseColor = texture(uTexture, TexCoords).rgb * baseColor;
    }
    
    vec3 lightDir;
    vec3 ambient;
    vec3 diffuseColor;

    if (uIsWhiteTurn) {
        // Day
        ambient = 0.6 * baseColor;
        lightDir = normalize(vec3(0.5, 1.0, 0.3));
        diffuseColor = vec3(0.8, 0.75, 0.7); // Warmer bright light
    } else {
        // Night
        ambient = 0.3 * baseColor;
        lightDir = normalize(vec3(-0.5, 1.0, -0.3));
        diffuseColor = vec3(0.4, 0.45, 0.6); // Cooler dark light
    }
    
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor * baseColor;
    
    vec3 result = ambient + diffuse;
    FragColor = vec4(result, uOpacity);
}
