#pragma once
#include <glimac/glm.hpp>
#include "ICamera.hpp"

class PovCamera : public ICamera {
private:
    float     m_angleX = 0.0f;
    float     m_angleY = 0.0f;
    glm::vec3 m_position; // The active piece position

public:
    PovCamera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const override;
    void processMouseDrag(float deltaX, float deltaY) override;
    void processMouseScroll(float scrollDelta) override;

    void setTargetPosition(const glm::vec3& pos);
};
