#pragma once

#include <string>
#include <glad/glad.h>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>

class BoardRenderer {
public:
    BoardRenderer(const std::string& prefixToUse);
    ~BoardRenderer();

    void draw(GLuint modelLoc, GLuint uColorOverrideLoc, GLuint uUseOverrideLoc, GLuint uHasTextureLoc, GLuint uTextureLoc, GLuint cubeVao);

private:
    GLuint m_textureLightTile = 0;
    GLuint m_textureDarkTile = 0;

    GLuint loadTexture(const std::string& path);
};
