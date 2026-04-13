#include "AIController.hpp"

void AIController::playAITurn(ChessGame& game)
{
    if (!m_enabled || game.getCurrentTurn() == m_playerColor || game.getState() != GameState::Playing)
        return;

    Move       aiMove;
    PieceColor aiColor = (m_playerColor == PieceColor::White) ? PieceColor::Black : PieceColor::White;

    if (AI::getBestMove(game.getBoard(), aiColor, m_difficulty, aiMove))
    {
        (void)game.move(aiMove.from, aiMove.to);
    }
}
