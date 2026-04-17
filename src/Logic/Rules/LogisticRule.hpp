#pragma once

#include <random>
#include "../IGameRule.hpp"

class LogisticRule : public IGameRule {
public:
    // mu = 5.0, s = 2.0. Seuil à 8.5 pour que la conversion soit rare mais possible.
    explicit LogisticRule(double mu = 5.0, double s = 2.0, double seuil = 6.5);
    ~LogisticRule() override = default;

    // On utilise overrideMove au lieu de onPieceCaptured
    bool overrideMove(Board& board, Position from, Position to) override;

    [[nodiscard]] std::string getRuleName() const override;
    [[nodiscard]] std::string getMathStats() const override;

private:
    double                                 m_mu;
    double                                 m_s;
    double                                 m_seuilPersuasion;
    std::mt19937                           m_gen;
    std::uniform_real_distribution<double> m_uniformDist;
};