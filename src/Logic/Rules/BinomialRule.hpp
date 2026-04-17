#pragma once

#include <random>
#include "../IGameRule.hpp"

class BinomialRule : public IGameRule {
public:
    // p = 0.15 by default: 15% chance for each dead piece to come back per turn
    explicit BinomialRule(double probability = 0.15);
    ~BinomialRule() override = default;

    void onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                                 m_probability;
    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};