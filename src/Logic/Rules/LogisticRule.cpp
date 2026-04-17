#include "LogisticRule.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

LogisticRule::LogisticRule(double mu, double s, double seuil)
    : m_mu(mu)
    , m_s(s)
    , m_seuilPersuasion(seuil)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0)
{
}

bool LogisticRule::overrideMove(Board& board, Position from, Position to)
{
    Piece attaquant = board.getPiece(from.x, from.y);
    Piece victime   = board.getPiece(to.x, to.y);

    // 1. Vérifier si le mouvement est bien une capture valide
    if (victime.isEmpty() || victime.color == attaquant.color || victime.type == PieceType::King)
    {
        return false; // Ce n'est pas une capture (ou c'est le Roi), on laisse le jeu faire son mouvement normal
    }

    // 2. Génération du score de "Persuasion" via la loi Logistique (avec U(0,1))
    double u = m_uniformDist(m_gen);
    while (u == 0.0 || u == 1.0)
    {
        u = m_uniformDist(m_gen);
    }

    // Formule mathématique d'inversion : X = mu + s * ln(U / (1 - U))
    double persuasion = m_mu + m_s * std::log(u / (1.0 - u));

    // 3. Vérification du seuil
    if (persuasion > m_seuilPersuasion)
    {
        // LA CONVERSION RÉUSSIT !

        // L'attaquant fait son mouvement normal (il prend la case 'to')
        board.setPiece(to.x, to.y, attaquant);

        // La victime change de couleur pour rejoindre celle de l'attaquant
        // et apparaît sur la case que l'attaquant vient juste de libérer ('from')
        board.setPiece(from.x, from.y, Piece{victime.type, attaquant.color});

        // On renvoie true pour dire au moteur "J'ai géré l'exécution du mouvement et la capture"
        return true;
    }

    // Si la persuasion a échoué, on renvoie false.
    // Le moteur de jeu s'occupera d'écraser la victime normalement.
    return false;
}

std::string LogisticRule::getRuleName() const
{
    return "La Conversion (Loi Logistique)";
}

std::string LogisticRule::getMathStats() const
{
    const double pi       = std::acos(-1.0);
    double       variance = (m_s * m_s * pi * pi) / 3.0;

    std::ostringstream oss;
    oss << "Loi Logistique (mu=" << std::fixed << std::setprecision(1) << m_mu
        << ", s=" << m_s << ") | Espérance : " << m_mu
        << " | Var : " << std::setprecision(2) << variance;
    return oss.str();
}

REGISTER_RULE(LogisticRule, "La Conversion (Loi Logistique)");