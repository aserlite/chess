#pragma once

#include <random>
#include "../IGameRule.hpp"

/**
 * @brief Loi de Poisson : "La Pluie de Météores"
 * Modélise le nombre d'impacts de météores par tour.
 */
class PoissonRule : public IGameRule {
public:
    explicit PoissonRule(double lambda = 1.0);

    void onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                                 m_lambda;
    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};
