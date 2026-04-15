#pragma once

#include <glad/glad.h>
#include <glimac/glm.hpp>
#include <map>
#include <string>
#include "../Logic/Piece.hpp"
#include "Model3D.hpp"

class PieceRenderer {
public:
    PieceRenderer(const std::string& prefixToUse);

    void draw(const Piece& p, float wx, float wz, GLint modelLoc, GLuint fallbackVao);

private:
    std::map<PieceType, Model3D> m_models;
};
