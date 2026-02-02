#pragma once
#include <array>
#include <vector>
#include "Piece.hpp"

class Board {
public:
    static constexpr int SIZE = 8;

    Board()
    {
        resetBoard();
    }

    void resetBoard()
    {
        for (auto& row : m_grid)
        {
            row.fill(Piece{});
        }

        for (int x = 0; x < SIZE; ++x)
        {
            m_grid[1][x] = Piece{PieceType::Pawn, PieceColor::Black};
            m_grid[6][x] = Piece{PieceType::Pawn, PieceColor::White};
        }

        setupNobleRow(0, PieceColor::Black);
        setupNobleRow(7, PieceColor::White);
    }

    const Piece& getPiece(int x, int y) const
    {
        return m_grid[y][x];
    }

    void setPiece(int x, int y, Piece p)
    {
        m_grid[y][x] = p;
    }

private:
    std::array<std::array<Piece, SIZE>, SIZE> m_grid;

    void setupNobleRow(int y, PieceColor color)
    {
        m_grid[y][0] = {PieceType::Rook, color};
        m_grid[y][1] = {PieceType::Knight, color};
        m_grid[y][2] = {PieceType::Bishop, color};
        m_grid[y][3] = {PieceType::Queen, color};

        m_grid[y][4] = {PieceType::King, color};
        m_grid[y][5] = {PieceType::Bishop, color};
        m_grid[y][6] = {PieceType::Knight, color};
        m_grid[y][7] = {PieceType::Rook, color};
    }
};