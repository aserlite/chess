#pragma once
#include <string>
#include <vector>
#include "AI.hpp"
#include "Board.hpp"

enum class GameState {
    Playing,
    PromotionSelect,
    WhiteWins,
    BlackWins
};

struct GameSnapshot {
    Board      board;
    PieceColor currentTurn;
    GameState  state;
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

    void undo();

    bool isVsAI() const { return m_vsAI; }
    void setVsAI(bool active) { m_vsAI = active; }

    void       playAITurn();
    void       setAIDifficulty(AIDifficulty diff) { m_aiDifficulty = diff; }
    void       setPlayerColor(PieceColor color) { m_playerColor = color; }
    PieceColor getPlayerColor() const { return m_playerColor; }

private:
    Board                    m_board;
    PieceColor               m_currentTurn;
    std::vector<std::string> m_history;

    GameState m_state;
    Position  m_promotionPos;

    void changeTurn();

    std::vector<GameSnapshot> m_backupHistory;
    void                      saveSnapshot();

    bool         m_vsAI         = false;
    AIDifficulty m_aiDifficulty = AIDifficulty::Easy;
    PieceColor   m_playerColor  = PieceColor::White;
};