#include "BernoulliRule.hpp"
#include <sstream>
#include <iomanip>

BernoulliRule::BernoulliRule(double probability)
    : m_probability(probability)
    , m_gen(std::random_device{}())
    , m_dist(probability)
{
}

bool BernoulliRule::overrideMove(Board& /*board*/, Position /*from*/, Position /*to*/)
{
    return m_dist(m_gen);
}

std::string BernoulliRule::getRuleName() const
{
    return "Loi de Bernoulli";
}

std::string BernoulliRule::getMathStats() const
{
    std::ostringstream oss;
    oss << "Probabilité d'échec : " << std::fixed << std::setprecision(1) << (m_probability * 100.0) << "%";
    return oss.str();
}

REGISTER_RULE(BernoulliRule, "Désobéissance (Loi de Bernoulli p=0.3)");
