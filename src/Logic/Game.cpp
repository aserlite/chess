#include "Game.hpp"
#include <cctype> // Pour toupper()

ChessGame::ChessGame()
    : m_currentTurn(PieceColor::White)
{
}

PieceColor ChessGame::getCurrentTurn() const
{
    return m_currentTurn;
}

const std::vector<std::string>& ChessGame::getHistory() const
{
    return m_history;
}

const Board& ChessGame::getBoard() const
{
    return m_board;
}

std::string ChessGame::toChessNotation(Position p) const
{
    char file = 'a' + p.x;
    char rank = '8' - p.y;
    return std::string(1, file) + std::string(1, rank);
}

bool ChessGame::move(Position from, Position to)
{
    if (m_board.isMoveValid(from, to) && m_board.getPiece(from.x, from.y).color == m_currentTurn)
    {
        std::string moveStr = toChessNotation(from) + toChessNotation(to);
        m_history.push_back(moveStr);

        Piece p = m_board.getPiece(from.x, from.y);
        m_board.setPiece(to.x, to.y, p);
        m_board.setPiece(from.x, from.y, Piece{PieceType::None, PieceColor::None});

        changeTurn();
        return true;
    }
    return false;
}

bool ChessGame::isValidMove(Position from, Position to) const
{
    if (m_board.getPiece(from.x, from.y).color != m_currentTurn)
        return false;

    return m_board.isMoveValid(from, to);
}

void ChessGame::changeTurn()
{
    m_currentTurn = (m_currentTurn == PieceColor::White) ? PieceColor::Black : PieceColor::White;
}

std::string ChessGame::getFEN() const
{
    std::string fen = "";

    for (int y = 0; y < 8; ++y)
    {
        int emptyCount = 0;
        for (int x = 0; x < 8; ++x)
        {
            Piece p = m_board.getPiece(x, y);

            if (p.isEmpty())
            {
                emptyCount++;
            }
            else
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                char c = '?';
                switch (p.type)
                {
                case PieceType::Pawn: c = 'p'; break;
                case PieceType::Rook: c = 'r'; break;
                case PieceType::Knight: c = 'n'; break;
                case PieceType::Bishop: c = 'b'; break;
                case PieceType::Queen: c = 'q'; break;
                case PieceType::King: c = 'k'; break;
                default: break;
                }

                if (p.color == PieceColor::White)
                {
                    c = std::toupper(c);
                }
                fen += c;
            }
        }

        if (emptyCount > 0)
        {
            fen += std::to_string(emptyCount);
        }

        if (y < 7)
        {
            fen += "/";
        }
    }

    fen += " ";
    fen += (m_currentTurn == PieceColor::White ? "w" : "b");
    fen += " - - 0 1";

    return fen;
}