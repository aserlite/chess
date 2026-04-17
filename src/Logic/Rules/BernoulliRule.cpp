#include "BernoulliRule.hpp"
#include <iomanip>
#include <sstream>

BernoulliRule::BernoulliRule(double probability)
    : m_probability(probability)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0) // Remplacement de l'ancienne distribution
{
}

bool BernoulliRule::overrideMove(Board& /*board*/, Position /*from*/, Position /*to*/)
{
    // On génère U sur [0, 1]. Si U < p, on considère que c'est un succès (échec du mouvement ici).
    return m_uniformDist(m_gen) < m_probability;
}

std::string BernoulliRule::getRuleName() const
{
    return "Désobéissance (Loi de Bernoulli)";
}

std::string BernoulliRule::getMathStats() const
{
    // Formules théoriques de la loi de Bernoulli
    double esperance = m_probability;
    double variance  = m_probability * (1.0 - m_probability);

    std::ostringstream oss;
    oss << "Loi de Bernoulli (p=" << std::fixed << std::setprecision(2) << m_probability << ")"
        << " | Espérance : " << esperance
        << " | Var : " << variance;
    return oss.str();
}

REGISTER_RULE(BernoulliRule, "Désobéissance (Loi de Bernoulli p=0.3)");