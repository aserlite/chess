#include "PoissonRule.hpp"
#include <cmath>
#include <iostream>
#include "../Game.hpp"

REGISTER_RULE(PoissonRule, "Loi de Poisson")

PoissonRule::PoissonRule(double lambda)
    : m_lambda(lambda)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0)
{
}

void PoissonRule::onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history)
{
    // Algorithme multiplicatif de Knuth pour la loi de Poisson
    const double L = std::exp(-m_lambda);
    double p = 1.0;
    int k = 0;

    do {
        k++;
        p *= m_uniformDist(m_gen);
    } while (p > L);

    int numMeteors = k - 1;

    for (int i = 0; i < numMeteors; ++i)
    {
        int x = std::uniform_int_distribution<int>(0, 7)(m_gen);
        int y = std::uniform_int_distribution<int>(0, 7)(m_gen);

        // On détruit ce qui se trouve sur la case
        board.setPiece(x, y, Piece{PieceType::None, PieceColor::None});
        
        // On enregistre l'événement pour la vue 3D
        history.push_back({{x, y}, {x, y}, "METEOR", false});
    }
}

std::string PoissonRule::getRuleName() const
{
    return "La Pluie de Météores (Poisson)";
}

std::string PoissonRule::getMathStats() const
{
    return "Loi de Poisson (lambda = " + std::to_string(m_lambda).substr(0, 4) + ")";
}
