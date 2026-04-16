#include "VictoryAnimator.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

void VictoryAnimator::update(float deltaTime, const ChessGame& game)
{
    const GameState state = game.getState();

    if (!m_active && state != GameState::Playing)
    {
        m_active      = true;
        m_winnerColor = (state == GameState::WhiteWins) ? PieceColor::White
                                                        : PieceColor::Black;
    }

    if (m_active)
        m_time += deltaTime;
}

void VictoryAnimator::reset()
{
    m_active = false;
    m_time   = 0.0f;
}

bool VictoryAnimator::isWinnerPiece(PieceColor c) const
{
    return m_active && c == m_winnerColor;
}

glm::mat4 VictoryAnimator::getDanceMatrix(float wx, float wz) const
{
    // Phase décalée par position pour effet organique
    const float phase  = wx * 0.4f + wz * 0.3f;
    const float t      = m_time * 2.0f + phase;
    const float bounce = std::abs(std::sin(t)) * 0.4f;
    const float lean   = std::sin(t) * glm::radians(15.0f);

    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bounce, 0.0f));
    m           = glm::rotate(m, lean, glm::vec3(0.0f, 0.0f, 1.0f));
    return m;
}

glm::vec3 VictoryAnimator::getDiscoColor(float phase) const
{
    const float h = std::fmod(m_time * 0.4f + phase, 1.0f);
    return hsvToRgb(h, 1.0f, 1.0f);
}

glm::vec3 VictoryAnimator::hsvToRgb(float h, float s, float v)
{
    const float c      = v * s;
    const float x      = c * (1.0f - std::abs(std::fmod(h * 6.0f, 2.0f) - 1.0f));
    const float m      = v - c;
    const int   sector = static_cast<int>(h * 6.0f) % 6;

    glm::vec3 rgb(0.0f);
    switch (sector)
    {
    case 0: rgb = {c, x, 0}; break;
    case 1: rgb = {x, c, 0}; break;
    case 2: rgb = {0, c, x}; break;
    case 3: rgb = {0, x, c}; break;
    case 4: rgb = {x, 0, c}; break;
    case 5: rgb = {c, 0, x}; break;
    }
    return rgb + glm::vec3(m);
}
