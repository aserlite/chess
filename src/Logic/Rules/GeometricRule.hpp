#pragma once

#include <random>
#include "../IGameRule.hpp"

class GeometricRule : public IGameRule {
public:
    explicit GeometricRule(double exhaustionProb = 0.4);
    bool overrideMove(Board& board, Position from, Position to) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                      m_prob;
    std::mt19937                m_gen;
    std::bernoulli_distribution m_dist;
};
