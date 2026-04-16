#pragma once

#include <imgui.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <memory>
#include <optional>
#include "../Logic/Game.hpp"
#include "3D/Framebuffer.hpp"
#include "3D/ICamera.hpp"
#include "3D/MousePicker.hpp"
#include "3D/PovCamera.hpp"
#include "3D/SceneRenderer.hpp"
#include "3D/TrackballCamera.hpp"
#include "ViewContext.hpp"

class ChessView3D {
public:
    ChessView3D();
    ~ChessView3D();

    // copy is forbidden (because of openGL memory allocation)
    ChessView3D(const ChessView3D&)            = delete;
    ChessView3D& operator=(const ChessView3D&) = delete;

    // move is allowed explicitly
    ChessView3D(ChessView3D&&)            = default;
    ChessView3D& operator=(ChessView3D&&) = default;

    void init();
    void draw(ChessGame& game, ViewContext& ctx);

private:
    void setupFramebuffer(const ImVec2& size);
    void updateAnimations(const ChessGame& game);

    std::unique_ptr<TrackballCamera> m_trackballCam;
    std::unique_ptr<PovCamera>       m_povCam;
    ICamera*                         m_activeCamera = nullptr;

    ChessVisualState             m_visualState;
    std::unique_ptr<MousePicker> m_mousePicker;

    std::unique_ptr<SceneRenderer> m_sceneRenderer;
    std::unique_ptr<Framebuffer>   m_framebuffer;

    struct MoveAnimation {
        Position from;
        Position to;
        Piece    piece;
        float    progress = 0.0f;
    };

    std::optional<MoveAnimation> m_activeAnim;
    size_t                       m_lastHistorySize = 0;
};
