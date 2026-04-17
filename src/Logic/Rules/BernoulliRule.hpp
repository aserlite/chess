#pragma once

#include <random>
#include "../IGameRule.hpp"

class BernoulliRule : public IGameRule {
public:
    explicit BernoulliRule(double probability = 0.3);

    bool overrideMove(Board& board, Position from, Position to) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                                 m_probability;
    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};
