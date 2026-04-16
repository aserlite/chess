#include "MousePicker.hpp"

std::optional<Position> MousePicker::getBoardPosition(const glm::vec2& mousePos, const glm::vec2& windowSize, const glm::mat4& view, const glm::mat4& proj)
{
    // 1. NDC Space (-1 to 1)
    float ndcX = (mousePos.x / windowSize.x) * 2.0f - 1.0f;
    float ndcY = 1.0f - (mousePos.y / windowSize.y) * 2.0f;

    // 2. Ray Direction in World Space
    glm::mat4 invProjView = glm::inverse(proj * view);
    glm::vec4 nearPoint   = invProjView * glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
    glm::vec4 farPoint    = invProjView * glm::vec4(ndcX, ndcY, 1.0f, 1.0f);

    glm::vec3 rayOrigin = glm::vec3(nearPoint) / nearPoint.w;
    glm::vec3 rayDir    = glm::normalize((glm::vec3(farPoint) / farPoint.w) - rayOrigin);

    // 3. Intersect with Plane y = 0
    if (std::abs(rayDir.y) < 0.0001f)
        return std::nullopt; // Parallel to board

    float t = -rayOrigin.y / rayDir.y;
    if (t < 0.0f)
        return std::nullopt; // Pointing away from board

    glm::vec3 hit = rayOrigin + rayDir * t;

    // 4. Convert World to Board Coordinates (-3.5 offset)
    int bx = static_cast<int>(std::round(hit.x + 3.5f));
    int bz = static_cast<int>(std::round(hit.z + 3.5f));

    if (bx >= 0 && bx < 8 && bz >= 0 && bz < 8)
    {
        return Position{bx, bz};
    }
    return std::nullopt;
}