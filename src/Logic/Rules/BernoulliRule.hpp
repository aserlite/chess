#pragma once

#include "../IGameRule.hpp"
#include <random>

class BernoulliRule : public IGameRule {
public:
    explicit BernoulliRule(double probability = 0.3);

    bool overrideMove(Board& board, Position from, Position to) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double m_probability;
    std::mt19937 m_gen;
    std::bernoulli_distribution m_dist;
};
