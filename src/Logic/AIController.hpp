#pragma once
#include "Game.hpp"
#include "AI.hpp"

class AIController {
public:
    AIController() = default;

    [[nodiscard]] bool isEnabled() const { return m_enabled; }
    void setEnabled(bool active) { m_enabled = active; }

    void setDifficulty(AIDifficulty diff) { m_difficulty = diff; }

    void setPlayerColor(PieceColor color) { m_playerColor = color; }
    [[nodiscard]] PieceColor getPlayerColor() const { return m_playerColor; }

    void playAITurn(ChessGame& game);

private:
    bool m_enabled = false;
    AIDifficulty m_difficulty = AIDifficulty::Easy;
    PieceColor m_playerColor = PieceColor::White;
};
