#pragma once
#include <imgui.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <optional>
#include <vector>
#include "../../Logic/Game.hpp"
#include "VictoryAnimator.hpp"

class ChessVisualState {
public:
    struct MovingPiece {
        Position from;
        Position to;
        Piece    piece;
        float    progress = 0.0f; // 0.0 to 1.0

        glm::vec3 getCurrentWorldPos() const
        {
            float t  = progress;
            float wx = (static_cast<float>(from.x) - 3.5f) + static_cast<float>(to.x - from.x) * t;
            float wz = (static_cast<float>(from.y) - 3.5f) + static_cast<float>(to.y - from.y) * t;

            float wy = std::sin(t * 3.14159265f) * 1.5f;

            return glm::vec3(wx, wy, wz);
        }
    };

    void update(float deltaTime, const ChessGame& game);

    // The Renderer loops through this to draw the moving pieces
    const std::vector<MovingPiece>& getActiveAnimations() const
    {
        return m_activeAnimations;
    }

    // The Camera uses this to figure out where to look
    std::optional<MovingPiece> getActiveAnimation() const;

    const VictoryAnimator& getVictoryAnimator() const { return m_victoryAnimator; }

private:
    std::vector<MovingPiece> m_activeAnimations;
    size_t                   m_lastHistorySize = 0;
    VictoryAnimator          m_victoryAnimator;
};