#include "BinomialRule.hpp"
#include <iomanip>
#include <sstream>

BinomialRule::BinomialRule(double probability)
    : m_probability(probability)
    , m_gen(std::random_device{}())
    , m_uniformDist(0.0, 1.0) // STRICT COMPLIANCE WITH 5(b)
{
}

void BinomialRule::onTurnStart(Board& board, PieceColor turn, std::vector<MoveLog>& history)
{
    // 1. Calculate how many pieces have been captured (n)
    // We do this by counting empty squares vs total possible pieces (32)
    int                   occupiedSquares = 0;
    std::vector<Position> emptySquares;

    for (int y = 0; y < static_cast<int>(Board::SIZE); ++y)
    {
        for (int x = 0; x < static_cast<int>(Board::SIZE); ++x)
        {
            if (board.getPiece(x, y).isEmpty())
            {
                emptySquares.push_back({x, y});
            }
            else
            {
                occupiedSquares++;
            }
        }
    }

    int n = 32 - occupiedSquares; // Number of captured pieces
    if (n <= 0 || emptySquares.empty())
        return;

    // 2. Generate B(n, p) using ONLY U(0,1)
    // The Binomial law is the sum of n independent Bernoulli trials
    int zombiesToSpawn = 0;
    for (int i = 0; i < n; ++i)
    {
        if (m_uniformDist(m_gen) < m_probability)
        {
            zombiesToSpawn++;
        }
    }

    // Safety clamp in case we generate more zombies than available board squares
    if (zombiesToSpawn > static_cast<int>(emptySquares.size()))
    {
        zombiesToSpawn = static_cast<int>(emptySquares.size());
    }

    // 3. Spawn the zombies
    for (int i = 0; i < zombiesToSpawn; ++i)
    {
        // Pick a random empty square using U(0,1)
        double u     = m_uniformDist(m_gen);
        int    index = static_cast<int>(u * emptySquares.size());

        // Safety clamp
        if (index >= emptySquares.size())
            index = emptySquares.size() - 1;

        Position pos = emptySquares[index];

        // Remove the chosen square from the list so we don't spawn two pieces on the same square
        emptySquares[index] = emptySquares.back();
        emptySquares.pop_back();

        // Spawn a Pawn of the current player's color
        board.setPiece(pos.x, pos.y, Piece{PieceType::Pawn, turn});

        history.push_back({pos, pos, "NECROMANCIE", false});
    }
}

std::string BinomialRule::getRuleName() const
{
    return "La Nécromancie";
}

std::string BinomialRule::getMathStats() const
{
    // Note: 'n' changes dynamically during the game, so we write the mathematical formula
    // rather than a hardcoded number for the expectation and variance.
    std::ostringstream oss;
    oss << "Loi Binomiale (p=" << std::fixed << std::setprecision(2) << m_probability << ")"
        << " | E[Z] = n*p | Var = n*p*(1-p) [n = pièces mortes]";
    return oss.str();
}

REGISTER_RULE(BinomialRule, "La Nécromancie (Loi Binomiale p=0.15)");