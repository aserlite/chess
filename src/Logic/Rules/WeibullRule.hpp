#pragma once

#include <random>
#include <map>
#include "../IGameRule.hpp"

/**
 * @brief La Malédiction de l'Usure (Loi de Weibull)
 * Modélise la fatigue matérielle des pièces qui s'accumule jusqu'à leur destruction.
 */
class WeibullRule : public IGameRule {
public:
    explicit WeibullRule(double lambda = 2.0, double k = 1.5, double seuil = 3.5);
    ~WeibullRule() override = default;

    // Simuler l'usure au début de chaque tour
    void onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double m_lambda;            // Paramètre d'échelle
    double m_k;                 // Paramètre de forme
    double m_seuilCritique;     // Seuil de destruction

    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};
