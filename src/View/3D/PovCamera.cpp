#include "PovCamera.hpp"
#include <algorithm>
#include <cmath>

[[nodiscard]] glm::mat4 PovCamera::getViewMatrix() const
{
    glm::vec3 direction(
        std::cos(m_angleY) * std::sin(m_angleX),
        std::sin(m_angleY),
        std::cos(m_angleY) * std::cos(m_angleX));

    return glm::lookAt(m_position, m_position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 PovCamera::getProjectionMatrix(float width, float height) const
{
    float aspect = width / height;
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
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

// Takes true 3D world coordinates
void PovCamera::setTargetPosition(const glm::vec3& worldPos)
{
    m_position = glm::vec3(worldPos.x, worldPos.y + 1.5f, worldPos.z);
}

// Takes logic board coordinates
void PovCamera::setTargetFromBoardPos(Position selectedPos)
{
    if (selectedPos.x != -1 && selectedPos.y != -1)
    {
        m_lastValidBoardPos = selectedPos;
    }

    // Convert the memory into 3D world space
    float px = static_cast<float>(m_lastValidBoardPos.x) - 3.5f;
    float pz = static_cast<float>(m_lastValidBoardPos.y) - 3.5f;

    m_position = glm::vec3(px, 1.5f, pz);
}