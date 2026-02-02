#pragma once
#include "Board.hpp"

class ChessGame {
public:
    ChessGame() = default;

    const Board& getBoard() const { return m_board; }

private:
    Board m_board;
};