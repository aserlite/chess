#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <glimac/glm.hpp>
#include "../Logic/Game.hpp"
#include "Model3D.hpp"

class PieceRenderer {
public:
    PieceRenderer(const std::string& prefixToUse);
    ~PieceRenderer() = default;

    void draw(const Piece& p, float wx, float wz, unsigned int modelLoc, unsigned int fallbackVao);

private:
    std::map<PieceType, Model3D> m_models;
};
