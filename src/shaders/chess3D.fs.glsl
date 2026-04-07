#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

uniform vec3 uColorOverride;
uniform bool uUseOverride;

void main() {
    if (uUseOverride) {
        FragColor = vec4(uColorOverride, 1.0);
    } else {
        FragColor = vec4(vertexColor, 1.0);
    }
}
