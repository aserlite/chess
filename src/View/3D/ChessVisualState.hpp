#include <imgui.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <optional>
#include <vector>
#include "../../Logic/Game.hpp"

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
            float wx = (from.x - 3.5f) + (to.x - from.x) * t;
            float wz = (from.y - 3.5f) + (to.y - from.y) * t;
            return glm::vec3(wx, 0.0f, wz);
        }
    };

private:
    std::vector<MovingPiece> m_activeAnimations;
    size_t                   m_lastHistorySize = 0;

public:
    void update(float deltaTime, const ChessGame& game);

    // The Renderer loops through this to draw the moving pieces
    const std::vector<MovingPiece>& getActiveAnimations() const
    {
        return m_activeAnimations;
    }

    // The Camera uses this to figure out where to look
    std::optional<MovingPiece> getActiveAnimation() const;
};