#include "ChessVisualState.hpp"

void ChessVisualState::update(float deltaTime, const ChessGame& game)
{
    const auto& history = game.getHistory();
    const auto& board   = game.getBoard();

    if (history.size() > m_lastHistorySize)
    {
        size_t newMovesCount = history.size() - m_lastHistorySize;

        for (size_t i = 0; i < newMovesCount; ++i)
        {
            const auto& move = history[m_lastHistorySize + i];
            if (move.actuallyMoved && move.from.x != -1)
            {
                MovingPiece anim;
                anim.from     = move.from;
                anim.to       = move.to;
                anim.piece    = board.getPiece(move.to.x, move.to.y);
                anim.progress = 0.0f;

                m_activeAnimations.push_back(anim);
            }
            else if (move.description == "METEOR")
            {
                MeteorAnim anim;
                anim.pos      = move.to;
                anim.progress = 0.0f;
                m_activeMeteors.push_back(anim);
            }
        }
        m_lastHistorySize = history.size();
    }
    else if (history.size() < m_lastHistorySize)
    {
        m_activeAnimations.clear();
        m_activeMeteors.clear();
        m_lastHistorySize = history.size();
        m_victoryAnimator.reset();
    }

    constexpr float animDuration = 0.5f;
    for (auto& anim : m_activeAnimations)
    {
        float dx         = static_cast<float>(anim.to.x - anim.from.x);
        float dy         = static_cast<float>(anim.to.y - anim.from.y);
        float distance   = std::sqrt(dx * dx + dy * dy);
        float travelTime = animDuration * std::max(1.0f, distance);
        anim.progress += deltaTime / (animDuration * travelTime);
    }

    std::erase_if(m_activeAnimations, [](const MovingPiece& anim) {
        return anim.progress >= 1.0f;
    });

    for (auto& meteor : m_activeMeteors)
    {
        meteor.progress += deltaTime * 1.5f; // Falls in ~0.66s
    }

    std::erase_if(m_activeMeteors, [](const MeteorAnim& m) {
        return m.progress >= 1.0f;
    });

    m_victoryAnimator.update(deltaTime, game);
}

std::optional<ChessVisualState::MovingPiece> ChessVisualState::getActiveAnimation() const
{
    if (!m_activeAnimations.empty())
    {
        return m_activeAnimations.back();
    }
    return std::nullopt;
}