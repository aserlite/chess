#pragma once
#include <array>
#include <cstddef>
#include "Piece.hpp"

class Board {
public:
    static constexpr std::size_t SIZE = 8;

    Board();

    void resetBoard();

    [[nodiscard]] Piece getPiece(int x, int y) const;
    void                setPiece(int x, int y, Piece p);

    [[nodiscard]] bool isMoveValid(Position from, Position to) const;

private:
    std::array<std::array<Piece, SIZE>, SIZE> m_grid{};

    void setupNobleRow(int y, PieceColor color);

    [[nodiscard]] bool isPathClear(Position from, Position to) const;

    [[nodiscard]] bool checkPawnMove(Position from, Position to, PieceColor color) const;
    [[nodiscard]] bool checkRookMove(Position from, Position to) const;
    [[nodiscard]] bool checkBishopMove(Position from, Position to) const;
    [[nodiscard]] bool checkKnightMove(Position from, Position to) const;
};