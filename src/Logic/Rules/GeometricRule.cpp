#include "GeometricRule.hpp"
#include <cmath>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include "../Piece.hpp"

GeometricRule::GeometricRule(double exhaustionProb)
    : m_prob(exhaustionProb)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0) // Remplacement strict pour valider la contrainte 5.b
{
}

bool GeometricRule::overrideMove(Board& board, Position from, Position to)
{
    const int dx = to.x - from.x;
    const int dy = to.y - from.y;

    const int steps = std::max(std::abs(dx), std::abs(dy));

    if (steps <= 1)
        return false;

    const int stepX = (dx > 0) - (dx < 0);
    const int stepY = (dy > 0) - (dy < 0);

    int curX = from.x + stepX;
    int curY = from.y + stepY;

    for (int i = 1; i < steps; ++i)
    {
        // Simulation d'une tentative de Bernoulli avec U(0,1) à chaque pas
        if (m_uniformDist(m_gen) < m_prob)
        {
            const Piece& obstacle = board.getPiece(curX, curY);
            if (!obstacle.isEmpty())
            {
                const int prevX = curX - stepX;
                const int prevY = curY - stepY;

                if (prevX == from.x && prevY == from.y)
                {
                    return true;
                }

                const Piece piece = board.getPiece(from.x, from.y);
                board.setPiece(prevX, prevY, piece);
                board.setPiece(from.x, from.y, Piece{.type = PieceType::None, .color = PieceColor::None});
                return true;
            }

            const Piece piece = board.getPiece(from.x, from.y);
            board.setPiece(curX, curY, piece);
            board.setPiece(from.x, from.y, Piece{.type = PieceType::None, .color = PieceColor::None});
            return true;
        }

        curX += stepX;
        curY += stepY;
    }

    return false;
}

std::string GeometricRule::getRuleName() const
{
    return "L'Essoufflement";
}

std::string GeometricRule::getMathStats() const
{
    // L'espérance et la variance étaient déjà mathématiquement correctes !
    const double esperance = 1.0 / m_prob;
    const double variance  = (1.0 - m_prob) / (m_prob * m_prob);

    std::ostringstream oss;
    oss << "Loi Géométrique (p=" << std::fixed << std::setprecision(2) << m_prob << ")"
        << " | Espérance : " << std::setprecision(2) << esperance
        << " | Var : " << std::setprecision(2) << variance;
    return oss.str();
}

REGISTER_RULE(GeometricRule, "L'Essoufflement (Loi Géométrique p=0.4)");