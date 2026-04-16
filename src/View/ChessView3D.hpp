#pragma once

#include <functional>
#include <imgui.h>
#include <memory>
#include <optional>
#include "3D/ChessVisualState.hpp"
#include "3D/ICamera.hpp"

// Forward declarations
class ChessGame;
struct ViewContext;
class Framebuffer;
class MousePicker;
class SceneRenderer;
class TrackballCamera;
class PovCamera;

class ChessView3D {
public:
    using OnMoveRequestedCb = std::function<void(Position from, Position to)>;

    explicit ChessView3D(OnMoveRequestedCb onMoveRequested);
    ~ChessView3D();

    // Prevent copying due to OpenGL resources
    ChessView3D(const ChessView3D&)            = delete;
    ChessView3D& operator=(const ChessView3D&) = delete;

    ChessView3D(ChessView3D&&)            = default;
    ChessView3D& operator=(ChessView3D&&) = default;

    void init();
    void draw(ChessGame& game, ViewContext& ctx);

private:
    // --- Internal Pipeline Steps ---
    void renderPipeline(const ChessGame& game, const ViewContext& ctx, const ImVec2& size, const std::optional<Position>& hoveredPos);
    void handleInput(const ChessGame& game, const std::optional<Position>& hoveredPos, ViewContext& ctx);
    void drawMenuBar();
    void updateAnimations(const ChessGame& game);

    // --- Sub-Systems ---
    std::unique_ptr<SceneRenderer> m_sceneRenderer;
    std::unique_ptr<Framebuffer>   m_framebuffer;
    std::unique_ptr<MousePicker>   m_mousePicker;

    // --- State ---
    std::unique_ptr<TrackballCamera> m_trackballCam;
    std::unique_ptr<PovCamera>       m_povCam;
    ICamera*                         m_activeCamera = nullptr;

    OnMoveRequestedCb m_onMoveRequested;
    ChessVisualState  m_visualState;
};
