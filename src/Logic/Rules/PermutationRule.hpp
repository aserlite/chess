#pragma once

#include <random>
#include "../IGameRule.hpp"

class PermutationRule : public IGameRule {
public:
    // activationProb = 0.05 : 5% de chance de déclencher le chaos à chaque début de tour
    explicit PermutationRule(double activationProb = 0.05);
    ~PermutationRule() override = default;

    void onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                                 m_activationProb;
    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};