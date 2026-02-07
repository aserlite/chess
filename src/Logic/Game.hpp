#pragma once
#include <string>
#include <vector>
#include "Board.hpp"

class ChessGame {
public:
    ChessGame();

    PieceColor                      getCurrentTurn() const;
    const std::vector<std::string>& getHistory() const;
    const Board&                    getBoard() const;

    std::string toChessNotation(Position p) const;

    bool move(Position from, Position to);
    bool isValidMove(Position from, Position to) const;

    std::string getFEN() const;

private:
    Board                    m_board;
    PieceColor               m_currentTurn;
    std::vector<std::string> m_history;

    void changeTurn();
};