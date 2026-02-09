#pragma once
#include "Board.hpp"
#include "Piece.hpp"

enum class AIDifficulty {
    Easy,   // Random
    Medium, // Gourmand
    Hard    // Minimax (plus tard)
};

struct Move {
    Position from;
    Position to;
};

class AI {
public:
    static bool getBestMove(const Board& board, PieceColor myColor, AIDifficulty level, Move& outMove);

private:
    static bool getRandomMove(const Board& board, PieceColor myColor, Move& outMove);
    static bool getGreedyMove(const Board& board, PieceColor myColor, Move& outMove);
};