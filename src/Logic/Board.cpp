#include "Board.hpp"
#include <cmath>

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    for (auto& row : m_grid)
    {
        row.fill(Piece{});
    }

    for (int x = 0; x < SIZE; ++x)
    {
        m_grid[1][x] = Piece{PieceType::Pawn, PieceColor::Black};
        m_grid[6][x] = Piece{PieceType::Pawn, PieceColor::White};
    }

    setupNobleRow(0, PieceColor::Black);
    setupNobleRow(7, PieceColor::White);
}

const Piece& Board::getPiece(int x, int y) const
{
    return m_grid[y][x];
}

void Board::setPiece(int x, int y, Piece p)
{
    m_grid[y][x] = p;
}

void Board::setupNobleRow(int y, PieceColor color)
{
    m_grid[y][0] = {PieceType::Rook, color};
    m_grid[y][1] = {PieceType::Knight, color};
    m_grid[y][2] = {PieceType::Bishop, color};
    m_grid[y][3] = {PieceType::Queen, color};
    m_grid[y][4] = {PieceType::King, color};
    m_grid[y][5] = {PieceType::Bishop, color};
    m_grid[y][6] = {PieceType::Knight, color};
    m_grid[y][7] = {PieceType::Rook, color};
}

bool Board::isMoveValid(Position from, Position to) const
{
    if (from == to)
        return false;
    if (to.x < 0 || to.x >= 8 || to.y < 0 || to.y >= 8)
        return false;

    const Piece& sourcePiece = getPiece(from.x, from.y);
    const Piece& targetPiece = getPiece(to.x, to.y);

    if (sourcePiece.isEmpty())
        return false;

    if (!targetPiece.isEmpty() && sourcePiece.color == targetPiece.color)
    {
        return false;
    }

    switch (sourcePiece.type)
    {
    case PieceType::Pawn:
        return checkPawnMove(from, to, sourcePiece.color);
    case PieceType::Rook:
        return checkRookMove(from, to) && isPathClear(from, to);
    case PieceType::Knight:
        return checkKnightMove(from, to);
    case PieceType::Bishop:
        return checkBishopMove(from, to) && isPathClear(from, to);
    case PieceType::Queen:
        return (checkRookMove(from, to) || checkBishopMove(from, to)) && isPathClear(from, to);
    case PieceType::King:
        return (std::abs(to.x - from.x) <= 1 && std::abs(to.y - from.y) <= 1);
    default:
        return false;
    }
}

bool Board::isPathClear(Position from, Position to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int currentX = from.x + stepX;
    int currentY = from.y + stepY;

    while (currentX != to.x || currentY != to.y)
    {
        if (!getPiece(currentX, currentY).isEmpty())
        {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }
    return true;
}

bool Board::checkPawnMove(Position from, Position to, PieceColor color) const
{
    int direction = (color == PieceColor::White) ? -1 : 1;
    int dx        = to.x - from.x;
    int dy        = to.y - from.y;

    if (dx == 0)
    {
        if (dy == direction)
        {
            return getPiece(to.x, to.y).isEmpty();
        }
        int startRow = (color == PieceColor::White) ? 6 : 1;
        if (dy == 2 * direction && from.y == startRow)
        {
            return getPiece(to.x, to.y).isEmpty() && getPiece(from.x, from.y + direction).isEmpty();
        }
    }
    else if (std::abs(dx) == 1 && dy == direction)
    {
        const Piece& target = getPiece(to.x, to.y);
        return !target.isEmpty() && target.color != color;
    }

    return false;
}

bool Board::checkRookMove(Position from, Position to) const
{
    return (from.x == to.x || from.y == to.y);
}

bool Board::checkBishopMove(Position from, Position to) const
{
    return std::abs(to.x - from.x) == std::abs(to.y - from.y);
}

bool Board::checkKnightMove(Position from, Position to) const
{
    int dx = std::abs(to.x - from.x);
    int dy = std::abs(to.y - from.y);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}