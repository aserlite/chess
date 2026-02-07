#pragma once
#include "Board.hpp"

class ChessGame {
public:
    bool move(Position from, Position to)
    {
        if (m_board.isMoveValid(from, to))
        {
            Piece p = m_board.getPiece(from.x, from.y);
            m_board.setPiece(to.x, to.y, p);
            m_board.setPiece(from.x, from.y, Piece{PieceType::None, PieceColor::None});

            return true;
        }
        return false;
    }

    bool isValidMove(Position from, Position to) const
    {
        return m_board.isMoveValid(from, to);
    }

    const Board& getBoard() const { return m_board; }

private:
    Board m_board;
};