#include "ExponentialRule.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

ExponentialRule::ExponentialRule(double lambda, double threshold)
    : m_lambda(lambda)
    , m_threshold(threshold)
    , m_gen(std::random_device{}())
{
}

void ExponentialRule::onTurnStart(Board& board, PieceColor /*turn*/)
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double u = 0.0;
    while (u == 0.0)
    {
        u = dist(m_gen);
    }

    double magnitude = -std::log(u) / m_lambda;

    if (magnitude > m_threshold)
    {
        std::uniform_int_distribution<int> lineDist(0, static_cast<int>(Board::SIZE) - 1);
        int targetY = lineDist(m_gen);

        for (int x = 0; x < static_cast<int>(Board::SIZE); ++x)
        {
            board.setPiece(x, targetY, Piece{PieceType::None, PieceColor::None});
        }
    }
}

std::string ExponentialRule::getRuleName() const
{
    return "Tremblement de Terre";
}

std::string ExponentialRule::getMathStats() const
{
    double esperance = 1.0 / m_lambda;
    double variance = 1.0 / (m_lambda * m_lambda);

    std::ostringstream oss;
    oss << "Loi Exponentielle -> Espérance : " << std::fixed << std::setprecision(2) << esperance 
        << " | Variance : " << variance;
    return oss.str();
}

REGISTER_RULE(ExponentialRule, "Tremblement de Terre (Loi Exponentielle)");
