#pragma once
#include <string>
#include <vector>
#include "Board.hpp"

enum class GameState {
    Playing,
    PromotionSelect,
    WhiteWins,
    BlackWins
};

class ChessGame {
public:
    ChessGame();

    PieceColor                      getCurrentTurn() const;
    const std::vector<std::string>& getHistory() const;
    const Board&                    getBoard() const;

    GameState getState() const { return m_state; }

    std::string toChessNotation(Position p) const;

    bool move(Position from, Position to);
    bool isValidMove(Position from, Position to) const;

    void promotePawn(PieceType type);

    std::string getFEN() const;
    void        loadFEN(const std::string& fen);

private:
    Board                    m_board;
    PieceColor               m_currentTurn;
    std::vector<std::string> m_history;

    GameState m_state;
    Position  m_promotionPos;

    void changeTurn();
};