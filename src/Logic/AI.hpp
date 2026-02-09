#pragma once
#include "Board.hpp"
#include "Piece.hpp"

struct Move {
    Position from;
    Position to;
};

class AI {
public:
    static bool getRandomMove(const Board& board, PieceColor myColor, Move& outMove);
};