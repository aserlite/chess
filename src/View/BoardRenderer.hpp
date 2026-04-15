#pragma once

#include <glad/glad.h>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <string>

class BoardRenderer {
public:
    BoardRenderer(const std::string& prefixToUse);
    ~BoardRenderer();

    // copy is forbidden (because of openGL memory allocation)
    BoardRenderer(const BoardRenderer&)            = delete;
    BoardRenderer& operator=(const BoardRenderer&) = delete;

    // move is allowed explicitly
    BoardRenderer(BoardRenderer&&)            = default;
    BoardRenderer& operator=(BoardRenderer&&) = default;

    void draw(GLuint modelLoc, GLuint uColorOverrideLoc, GLuint uUseOverrideLoc, GLuint uHasTextureLoc, GLuint uTextureLoc, GLuint cubeVao);

private:
    GLuint m_textureLightTile = 0;
    GLuint m_textureDarkTile  = 0;

    GLuint loadTexture(const std::string& path);
};
