#pragma once

enum class PieceColor {
    None,
    White,
    Black
};

enum class PieceType {
    None,   // Case vide
    Pawn,   // Pion
    Rook,   // Tour
    Knight, // Cavalier
    Bishop, // Fou
    Queen,  // Dame
    King    // Roi
};

struct Piece {
    PieceType  type  = PieceType::None;
    PieceColor color = PieceColor::None;

    bool isEmpty() const
    {
        return type == PieceType::None;
    }
};

struct Position {
    int x;
    int y;

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};