#pragma once
#include <optional>
#include <glimac/glm.hpp>
#include "ICamera.hpp"
#include "Logic/Piece.hpp"

class PovCamera : public ICamera {
private:
    float     m_angleX = 0.0f;
    float     m_angleY = 0.0f;
    glm::vec3 m_position{0.0f, 0.0f, 0.0f}; // The active piece position

    Position             m_lastValidBoardPos = {3, 3};
    std::optional<float> m_targetAngleX      = std::nullopt;

public:
    PovCamera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const override;
    void                    processMouseDrag(float deltaX, float deltaY) override;
    void                    processMouseScroll(float scrollDelta) override;

    void setTargetPosition(const glm::vec3& pos);
    void setTargetFromBoardPos(Position selectedPos);
    void setMemory(Position pos)
    {
        if (pos.x != -1 && pos.y != -1)
        {
            m_lastValidBoardPos = pos;
        }
    }

    void setTargetAngle(float targetAngleRadians)
    {
        m_targetAngleX = targetAngleRadians;
    }

    void setLookDirection(Position from, Position to)
    {
        float dx = static_cast<float>(to.x - from.x);
        float dz = static_cast<float>(to.y - from.y);

        if (dx != 0.0f || dz != 0.0f)
        {
            m_targetAngleX = std::atan2(dx, dz);
        }
    }

    void clearLookDirection()
    {
        m_targetAngleX = std::nullopt;
    }

    void updateRotation(float deltaTime)
    {
        if (m_targetAngleX.has_value())
        {
            float target = m_targetAngleX.value();
            float diff   = target - m_angleX;

            constexpr float PI = 3.14159265359f;
            while (diff <= -PI)
                diff += 2.0f * PI;
            while (diff > PI)
                diff -= 2.0f * PI;

            m_angleX += diff * 6.0f * deltaTime;
        }
    }
};
