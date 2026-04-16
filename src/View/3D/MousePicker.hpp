#pragma once
#include <glimac/glm.hpp>
#include <optional>
#include "Logic/Piece.hpp"

class MousePicker {
public:
    // Returns the board square (0-7) under the mouse, or nullopt if missing the board
    std::optional<Position> getBoardPosition(
        const glm::vec2& mousePos,
        const glm::vec2& windowSize,
        const glm::mat4& view,
        const glm::mat4& proj
    );
};