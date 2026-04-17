#pragma once
#include <cstdint>

enum class PieceColor : std::uint8_t {
    None,
    White,
    Black
};

enum class PieceType : std::uint8_t {
    None,   // Case vide
    Pawn,   // Pion
    Rook,   // Tour
    Knight, // Cavalier
    Bishop, // Fou
    Queen,  // Dame
    King    // Roi
};

struct Piece {
    PieceType  type      = PieceType::None;
    PieceColor color     = PieceColor::None;
    float      fatigue   = 0.0f;
    bool       isZombie  = false;

    [[nodiscard]] constexpr bool isEmpty() const noexcept
    {
        return type == PieceType::None;
    }
};

struct Position {
    int x{0};
    int y{0};

    [[nodiscard]] constexpr bool operator==(const Position& other) const noexcept
    {
        return x == other.x && y == other.y;
    }
};