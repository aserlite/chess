#pragma once
#include <glimac/glm.hpp>
#include "ICamera.hpp"

class TrackballCamera : public ICamera {
private:
    float m_distance = 15.0f;
    float m_angleX   = 0.0f;
    float m_angleY   = 0.7f;

public:
    TrackballCamera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const override;
    [[nodiscard]] glm::mat4 getProjectionMatrix(float width, float height) const override;

    void processMouseDrag(float deltaX, float deltaY) override;
    void processMouseScroll(float scrollDelta) override;
};
