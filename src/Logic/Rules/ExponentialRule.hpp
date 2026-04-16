#pragma once

#include "../IGameRule.hpp"
#include <random>

class ExponentialRule : public IGameRule {
public:
    explicit ExponentialRule(double lambda = 1.0, double threshold = 2.0);

    void onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double m_lambda;
    double m_threshold;
    std::mt19937 m_gen;
};
