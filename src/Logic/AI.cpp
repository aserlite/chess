#include "AI.hpp"
#include <ctime>
#include <random>
#include <vector>

bool AI::getRandomMove(const Board& board, PieceColor myColor, Move& outMove)
{
    std::vector<Move> possibleMoves;

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            Piece p = board.getPiece(x, y);

            if (!p.isEmpty() && p.color == myColor)
            {
                for (int ty = 0; ty < 8; ++ty)
                {
                    for (int tx = 0; tx < 8; ++tx)
                    {
                        Position from = {x, y};
                        Position to   = {tx, ty};

                        if (board.isMoveValid(from, to))
                        {
                            possibleMoves.push_back({from, to});
                        }
                    }
                }
            }
        }
    }

    if (possibleMoves.empty())
    {
        return false;
    }

    static std::mt19937                rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);

    int randomIndex = dist(rng);
    outMove         = possibleMoves[randomIndex];

    return true;
}