#pragma once
#include "Board.hpp"

class ChessGame {
public:
    ChessGame()
        : m_currentTurn(PieceColor::White) {}
    PieceColor getCurrentTurn() const { return m_currentTurn; }

    bool move(Position from, Position to)
    {
        Piece p = m_board.getPiece(from.x, from.y);

        if (p.color != m_currentTurn)
        {
            return false;
        }
        if (m_board.isMoveValid(from, to))
        {
            m_board.setPiece(to.x, to.y, p);
            m_board.setPiece(from.x, from.y, Piece{PieceType::None, PieceColor::None});

            changeTurn();

            return true;
        }
        return false;
    }

    bool isValidMove(Position from, Position to) const
    {
        if (m_board.getPiece(from.x, from.y).color != m_currentTurn)
            return false;

        return m_board.isMoveValid(from, to);
    }

    const Board& getBoard() const { return m_board; }

private:
    Board      m_board;
    PieceColor m_currentTurn;
    void       changeTurn()
    {
        m_currentTurn = (m_currentTurn == PieceColor::White) ? PieceColor::Black : PieceColor::White;
    }
};