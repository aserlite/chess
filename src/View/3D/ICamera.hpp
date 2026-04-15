#pragma once
#include <glm/glm.hpp>

class ICamera {
public:
    virtual ~ICamera() = default;

    ICamera(const ICamera&)            = delete;
    ICamera& operator=(const ICamera&) = delete;
    ICamera(ICamera&&)                 = delete;
    ICamera& operator=(ICamera&&)      = delete;

protected:
    ICamera() = default;

public:
    [[nodiscard]] virtual glm::mat4 getViewMatrix() const = 0;

    virtual void processMouseDrag(float deltaX, float deltaY) = 0;
    virtual void processMouseScroll(float scrollDelta)        = 0;
};