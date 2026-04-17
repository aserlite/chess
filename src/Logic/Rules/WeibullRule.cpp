#include "WeibullRule.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>

WeibullRule::WeibullRule(double lambda, double k, double seuil)
    : m_lambda(lambda)
    , m_k(k)
    , m_seuilCritique(seuil)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0)
{
}

void WeibullRule::onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history)
{
    // 1. Identifier les pièces du joueur actuel (hors Rois)
    std::vector<Position> targets;
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            Piece p = board.getPiece(x, y);
            if (!p.isEmpty() && p.color == turn && p.type != PieceType::King)
            {
                targets.push_back({x, y});
            }
        }
    }

    if (targets.empty()) return;

    // Sélection aléatoire d'une pièce victime
    std::uniform_int_distribution<int> selectDist(0, static_cast<int>(targets.size()) - 1);
    Position targetPos = targets[selectDist(m_gen)];
    
    Piece p = board.getPiece(targetPos.x, targetPos.y);

    // 2. Génération de la variable aléatoire de Weibull par inversion
    double u = m_uniformDist(m_gen);
    // Protection du logarithme (U != 1.0 car ln(1-U) -> ln(0) est indéfini)
    while (u >= 1.0) { u = m_uniformDist(m_gen); }

    // X = lambda * (-ln(1 - U))^(1 / k)
    double fatigueIncrement = m_lambda * std::pow(-std::log(1.0 - u), 1.0 / m_k);

    // Accumulation de la fatigue directement dans la pièce
    p.fatigue += static_cast<float>(fatigueIncrement);
    board.setPiece(targetPos.x, targetPos.y, p);

    // Notification pour l'historique (le renderer lira p.fatigue)
    history.push_back({targetPos, targetPos, "USURE:" + std::to_string(p.fatigue), false});

    // 3. Vérification du seuil critique
    if (p.fatigue > m_seuilCritique)
    {
        board.setPiece(targetPos.x, targetPos.y, Piece{PieceType::None, PieceColor::None});
        history.push_back({targetPos, targetPos, "DETRUITE (Sénescence)", false});
    }
}

std::string WeibullRule::getRuleName() const
{
    return "La Malédiction de l'Usure";
}

std::string WeibullRule::getMathStats() const
{
    // Espérance = lambda * Gamma(1 + 1/k)
    double esperance = m_lambda * std::tgamma(1.0 + 1.0 / m_k);
    
    // Variance = lambda^2 * [Gamma(1 + 2/k) - (Gamma(1 + 1/k))^2]
    double term1 = std::tgamma(1.0 + 2.0 / m_k);
    double term2 = std::pow(std::tgamma(1.0 + 1.0 / m_k), 2.0);
    double variance  = (m_lambda * m_lambda) * (term1 - term2);

    std::ostringstream oss;
    oss << "Weibull(λ=" << std::fixed << std::setprecision(1) << m_lambda 
        << ", k=" << m_k << ") | E[X]=" << std::setprecision(2) << esperance 
        << " | Var=" << variance;
    return oss.str();
}

REGISTER_RULE(WeibullRule, "Usure (Loi de Weibull)");
