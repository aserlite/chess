#pragma once

#include "../IGameRule.hpp"
#include <random>

class GaussianRule : public IGameRule {
public:
    explicit GaussianRule(double mu = 1.0, double variance = 1.5);

    void onPieceCaptured(Board& board, Position pos) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double m_mu;
    double m_variance;
    std::mt19937 m_gen;
};
