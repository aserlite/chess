#pragma once

#include <glimac/glm.hpp>
#include "../../Logic/Game.hpp"

// Animations de victoire : disco RGB + danse des pièces gagnantes
class VictoryAnimator {
public:
    void update(float deltaTime, const ChessGame& game);
    void reset();

    bool      isActive()                         const { return m_active; }
    bool      isWinnerPiece(PieceColor c)        const;
    glm::mat4 getDanceMatrix(float wx, float wz) const; // saut + penché
    glm::vec3 getDiscoColor(float phase = 0.0f)  const; // HSV cycling

private:
    bool       m_active      = false;
    float      m_time        = 0.0f;
    PieceColor m_winnerColor = PieceColor::White;

    static glm::vec3 hsvToRgb(float h, float s, float v);
};
