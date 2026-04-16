#include "TrackballCamera.hpp"
#include <algorithm>
#include <cmath>

[[nodiscard]] glm::mat4 TrackballCamera::getViewMatrix() const
{
    const float camX = m_distance * std::cos(m_angleY) * std::sin(m_angleX);
    const float camY = m_distance * std::sin(m_angleY);
    const float camZ = m_distance * std::cos(m_angleY) * std::cos(m_angleX);

    return glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 TrackballCamera::getProjectionMatrix(float width, float height) const
{
    float aspect = width / height;
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}

void TrackballCamera::processMouseDrag(float deltaX, float deltaY)
{
    m_angleX -= deltaX * 0.01f;
    m_angleY -= deltaY * 0.01f;
    m_angleY = std::max(0.0f, std::min(1.57f, m_angleY));
}

void TrackballCamera::processMouseScroll(float scrollDelta)
{
    m_distance -= scrollDelta * 1.5f;
    m_distance = std::max(2.0f, std::min(30.0f, m_distance));
}