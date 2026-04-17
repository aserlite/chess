#include "PermutationRule.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

PermutationRule::PermutationRule(double activationProb)
    : m_activationProb(activationProb)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0) // STRICTEMENT conforme à la contrainte 5(b)
{
}

void PermutationRule::onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history)
{
    // 1. Déterminer si le chaos se déclenche ce tour-ci avec U(0,1)
    if (m_uniformDist(m_gen) > m_activationProb)
    {
        return; // Pas de chaos ce tour-ci
    }

    // 2. Récupérer toutes les positions des pièces du joueur actuel
    std::vector<Position> playerPieces;
    for (int y = 0; y < static_cast<int>(Board::SIZE); ++y)
    {
        for (int x = 0; x < static_cast<int>(Board::SIZE); ++x)
        {
            const Piece& p = board.getPiece(x, y);
            if (!p.isEmpty() && p.color == turn)
            {
                playerPieces.push_back({x, y});
            }
        }
    }

    int n = static_cast<int>(playerPieces.size());

    // S'il n'y a qu'une seule pièce (ex: juste le roi), on ne peut rien échanger
    if (n < 2)
        return;

    // 3. Algorithme de Fisher-Yates, alimenté EXCLUSIVEMENT par U(0, 1)
    // On parcourt le tableau à l'envers et on échange l'élément i avec un élément j tiré au sort (j <= i)
    for (int i = n - 1; i > 0; --i)
    {
        // Tirage de U(0,1). On gère le cas extrême (et très rare) où U == 1.0 exact
        // pour éviter que std::floor ne renvoie i + 1, ce qui ferait planter le tableau.
        double u = m_uniformDist(m_gen);
        while (u >= 1.0)
        {
            u = m_uniformDist(m_gen);
        }

        // Transformation de la variable continue U en indice discret j sur [0, i]
        int j = static_cast<int>(std::floor(u * (i + 1)));

        // Récupération des positions sur le plateau
        Position pos1 = playerPieces[i];
        Position pos2 = playerPieces[j];

        // Échange logique des pièces sur le plateau
        Piece piece1 = board.getPiece(pos1.x, pos1.y);
        Piece piece2 = board.getPiece(pos2.x, pos2.y);

        board.setPiece(pos1.x, pos1.y, piece2);
        board.setPiece(pos2.x, pos2.y, piece1);

        // Optionnel : ajouter un signal visuel pour l'interface si l'échange a eu lieu
        if (i != j)
        {
            history.push_back({pos1, pos2, "CHAOS_SWAP", false});
        }
    }
}

std::string PermutationRule::getRuleName() const
{
    return "Le Chaos Royal";
}

std::string PermutationRule::getMathStats() const
{
    // L'espérance ici n'a pas de sens numérique car on mélange des objets (les pièces).
    // On met donc en avant la probabilité uniforme d'obtenir n'importe quelle configuration.
    std::ostringstream oss;
    oss << "Permutation Aléatoire (Fisher-Yates)"
        << " | Probabilité d'une configuration : 1/n! (n = nb pièces)";
    return oss.str();
}

REGISTER_RULE(PermutationRule, "Les Chaises Musicales (Permutation de Fisher-Yates)");