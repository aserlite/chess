#pragma once
#include <array>
#include "Piece.hpp"

class Board {
public:
    static constexpr int SIZE = 8;

    Board();

    void resetBoard();
    
    const Piece& getPiece(int x, int y) const;
    void setPiece(int x, int y, Piece p);

    bool isMoveValid(Position from, Position to) const;

private:
    std::array<std::array<Piece, SIZE>, SIZE> m_grid;

    void setupNobleRow(int y, PieceColor color);

    bool isPathClear(Position from, Position to) const;
    
    bool checkPawnMove(Position from, Position to, PieceColor color) const;
    bool checkRookMove(Position from, Position to) const;
    bool checkBishopMove(Position from, Position to) const;
    bool checkKnightMove(Position from, Position to) const;
};