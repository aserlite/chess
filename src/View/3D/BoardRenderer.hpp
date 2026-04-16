#pragma once

#include <glad/glad.h>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <string>
#include <optional>
#include "../../Logic/Game.hpp"
#include "../ViewContext.hpp"

class VictoryAnimator;

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

    void draw(GLint modelLoc, GLint uColorOverrideLoc, GLint uUseOverrideLoc, GLint uHasTextureLoc, GLint uTextureLoc, GLuint cubeVao, const ChessGame& game, const ViewContext& ctx, std::optional<Position> hoveredPos, const VictoryAnimator* va = nullptr);

private:
    GLuint m_textureLightTile = 0;
    GLuint m_textureDarkTile  = 0;

    GLuint loadTexture(const std::string& path);
};
