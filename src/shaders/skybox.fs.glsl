#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 uTint;

void main() {    
    FragColor = vec4(texture(skybox, TexCoords).rgb * uTint, 1.0);
}