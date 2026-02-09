#include "AI.hpp"
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

bool AI::getBestMove(const Board& board, PieceColor myColor, AIDifficulty level, Move& outMove)
{
    if (level == AIDifficulty::Easy)
    {
        return getRandomMove(board, myColor, outMove);
    }
    else if (level == AIDifficulty::Medium)
    {
        return getGreedyMove(board, myColor, outMove);
    }
    return getGreedyMove(board, myColor, outMove);
}

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

bool AI::getGreedyMove(const Board& board, PieceColor myColor, Move& outMove)
{
    std::vector<Move> possibleMoves;
    int               bestScore = -9999;
    std::vector<Move> bestMoves;

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
                            int   score  = 0;
                            Piece target = board.getPiece(tx, ty);

                            if (!target.isEmpty())
                            {
                                switch (target.type)
                                {
                                case PieceType::Pawn: score = 10; break;
                                case PieceType::Knight: score = 30; break;
                                case PieceType::Bishop: score = 30; break;
                                case PieceType::Rook: score = 50; break;
                                case PieceType::Queen: score = 90; break;
                                case PieceType::King: score = 900; break;
                                default: break;
                                }
                            }

                            if (score > bestScore)
                            {
                                bestScore = score;
                                bestMoves.clear();
                                bestMoves.push_back({from, to});
                            }
                            else if (score == bestScore)
                            {
                                bestMoves.push_back({from, to});
                            }
                        }
                    }
                }
            }
        }
    }

    if (bestMoves.empty())
        return false;

    static std::mt19937                rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, bestMoves.size() - 1);
    outMove = bestMoves[dist(rng)];

    return true;
}