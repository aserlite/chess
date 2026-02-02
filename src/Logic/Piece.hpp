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