#include "Game.hpp"
#include <cctype> // Pour toupper()
#include "AI.hpp"

ChessGame::ChessGame()
    : m_currentTurn(PieceColor::White)
    , m_state(GameState::Playing)
    , m_promotionPos{-1, -1}
    , m_vsAI(false)
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
    if (m_state != GameState::Playing)
        return false;

    if (m_board.isMoveValid(from, to) && m_board.getPiece(from.x, from.y).color == m_currentTurn)
    {
        saveSnapshot();
        Piece target = m_board.getPiece(to.x, to.y);
        if (target.type == PieceType::King)
        {
            m_state = (m_currentTurn == PieceColor::White) ? GameState::WhiteWins : GameState::BlackWins;

            Piece p = m_board.getPiece(from.x, from.y);
            m_board.setPiece(to.x, to.y, p);
            m_board.setPiece(from.x, from.y, Piece{PieceType::None, PieceColor::None});

            m_history.push_back(toChessNotation(from) + toChessNotation(to) + "#");
            return true;
        }

        std::string moveStr = toChessNotation(from) + toChessNotation(to);

        Piece p = m_board.getPiece(from.x, from.y);
        m_board.setPiece(to.x, to.y, p);
        m_board.setPiece(from.x, from.y, Piece{PieceType::None, PieceColor::None});

        bool isPawn = (p.type == PieceType::Pawn);
        bool endRow = (p.color == PieceColor::White && to.y == 0) || (p.color == PieceColor::Black && to.y == 7);

        if (isPawn && endRow)
        {
            m_state        = GameState::PromotionSelect;
            m_promotionPos = to;
            return true;
        }

        m_history.push_back(moveStr);
        changeTurn();
        return true;
    }
    return false;
}

void ChessGame::promotePawn(PieceType type)
{
    if (m_state != GameState::PromotionSelect)
        return;

    Piece p = m_board.getPiece(m_promotionPos.x, m_promotionPos.y);
    p.type  = type;
    m_board.setPiece(m_promotionPos.x, m_promotionPos.y, p);

    std::string promoChar;
    if (type == PieceType::Queen)
        promoChar = "q";
    else if (type == PieceType::Rook)
        promoChar = "r";
    else if (type == PieceType::Bishop)
        promoChar = "b";
    else
        promoChar = "n";

    m_history.push_back("promotion=" + promoChar);

    m_state        = GameState::Playing;
    m_promotionPos = {-1, -1};
    changeTurn();
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

void ChessGame::loadFEN(const std::string& fen)
{
    m_board.resetBoard();

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            m_board.setPiece(x, y, Piece{PieceType::None, PieceColor::None});
        }
    }

    int x = 0;
    int y = 0;

    size_t i = 0;
    for (; i < fen.length(); ++i)
    {
        char c = fen[i];

        if (c == ' ')
            break;

        if (c == '/')
        {
            y++;
            x = 0;
        }
        else if (isdigit(c))
        {
            x += (c - '0');
        }
        else
        {
            PieceColor color  = isupper(c) ? PieceColor::White : PieceColor::Black;
            PieceType  type   = PieceType::None;
            char       lowerC = tolower(c);

            switch (lowerC)
            {
            case 'p': type = PieceType::Pawn; break;
            case 'r': type = PieceType::Rook; break;
            case 'n': type = PieceType::Knight; break;
            case 'b': type = PieceType::Bishop; break;
            case 'q': type = PieceType::Queen; break;
            case 'k': type = PieceType::King; break;
            }

            if (x < 8 && y < 8)
            {
                m_board.setPiece(x, y, Piece{type, color});
                x++;
            }
        }
    }

    if (i + 1 < fen.length())
    {
        char turn     = fen[i + 1];
        m_currentTurn = (turn == 'w') ? PieceColor::White : PieceColor::Black;
    }

    m_history.clear();
    m_state = GameState::Playing;
}

void ChessGame::saveSnapshot()
{
    GameSnapshot snapshot;
    snapshot.board       = m_board;
    snapshot.currentTurn = m_currentTurn;
    snapshot.state       = m_state;

    m_backupHistory.push_back(snapshot);
}

void ChessGame::undo()
{
    if (m_backupHistory.empty())
        return;

    GameSnapshot lastState = m_backupHistory.back();

    m_board       = lastState.board;
    m_currentTurn = lastState.currentTurn;
    m_state       = lastState.state;

    m_backupHistory.pop_back();

    if (!m_history.empty())
    {
        m_history.pop_back();
    }
}

void ChessGame::playAITurn()
{
    if (m_currentTurn == m_playerColor || m_state != GameState::Playing)
        return;

    Move       aiMove;
    PieceColor aiColor = (m_playerColor == PieceColor::White) ? PieceColor::Black : PieceColor::White;

    if (AI::getBestMove(m_board, aiColor, m_aiDifficulty, aiMove))
    {
        move(aiMove.from, aiMove.to);
    }
}