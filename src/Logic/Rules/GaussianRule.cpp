#include "GaussianRule.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

GaussianRule::GaussianRule(double mu, double variance)
    : m_mu(mu)
    , m_variance(variance)
    , m_gen(std::random_device{}())
{
}

void GaussianRule::onPieceCaptured(Board& board, Position pos)
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double u1 = 0.0;
    while (u1 == 0.0)
    {
        u1 = dist(m_gen);
    }
    double u2 = dist(m_gen);

    const double PI = std::acos(-1.0);
    double z = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * PI * u2);
    
    double r = m_mu + std::sqrt(m_variance) * z;
    double radius = std::max(0.0, r); 

    for (int x = 0; x < static_cast<int>(Board::SIZE); ++x)
    {
        for (int y = 0; y < static_cast<int>(Board::SIZE); ++y)
        {
            double dx = static_cast<double>(x - pos.x);
            double dy = static_cast<double>(y - pos.y);
            double d = std::sqrt(dx * dx + dy * dy);
            
            if (d <= radius)
            {
                board.setPiece(x, y, Piece{PieceType::None, PieceColor::None});
            }
        }
    }
}

std::string GaussianRule::getRuleName() const
{
    return "Pièces Explosives";
}

std::string GaussianRule::getMathStats() const
{
    std::ostringstream oss;
    oss << "Loi Normale -> Espérance : " << std::fixed << std::setprecision(2) << m_mu 
        << " | Variance : " << m_variance;
    return oss.str();
}

REGISTER_RULE(GaussianRule, "Pièces Explosives (Loi de Gauss)");
