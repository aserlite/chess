#include "PovCamera.hpp"
#include <algorithm>
#include <cmath>

[[nodiscard]] glm::mat4 PovCamera::getViewMatrix() const
{
    const float lookX = std::sin(m_angleX) * std::cos(m_angleY);
    const float lookY = std::sin(m_angleY);
    const float lookZ = std::cos(m_angleX) * std::cos(m_angleY);

    return glm::lookAt(m_position, m_position + glm::vec3(lookX, lookY, lookZ), glm::vec3(0.0f, 1.0f, 0.0f));
}

void PovCamera::processMouseDrag(float deltaX, float deltaY)
{
    m_angleX -= deltaX * 0.01f;
    m_angleY -= deltaY * 0.01f;
    m_angleY = std::max(-1.55f, std::min(1.55f, m_angleY));
}

void PovCamera::processMouseScroll(float /*scrollDelta*/)
{
    // No zoom for the POV camera :(
}

void PovCamera::setTargetPosition(const glm::vec3& pos)
{
    m_position = pos;
}