#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Board.hpp"

class IGameRule;

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
    ChessGame() = default;

    void addRule(std::shared_ptr<IGameRule> rule)
    {
        m_activeRules.push_back(std::move(rule));
    }
    void clearRules()
    {
        m_activeRules.clear();
    }

    [[nodiscard]] PieceColor                      getCurrentTurn() const { return m_currentTurn; }
    [[nodiscard]] const std::vector<std::string>& getHistory() const { return m_history; }
    [[nodiscard]] const Board&                    getBoard() const { return m_board; }
    [[nodiscard]] GameState                       getState() const { return m_state; }

    [[nodiscard]] std::string toChessNotation(Position p) const;

    [[nodiscard]] bool move(Position from, Position to);
    [[nodiscard]] bool isValidMove(Position from, Position to) const;

    void promotePawn(PieceType type);

    [[nodiscard]] std::string getFEN() const;
    void                      loadFEN(const std::string& fen);

    void undo();

private:
    Board                    m_board;
    PieceColor               m_currentTurn = PieceColor::White;
    std::vector<std::string> m_history;

    GameState m_state        = GameState::Playing;
    Position  m_promotionPos = {-1, -1};

    std::vector<std::shared_ptr<IGameRule>> m_activeRules;

    void changeTurn();

    std::vector<GameSnapshot> m_backupHistory;
    void                      saveSnapshot();
};