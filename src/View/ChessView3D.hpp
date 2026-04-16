#pragma once

#include <imgui.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <memory>
#include <optional>
#include "../Logic/Game.hpp"
#include "3D/BoardRenderer.hpp"
#include "3D/ChessVisualState.hpp"
#include "3D/CubeMesh.hpp"
#include "3D/ICamera.hpp"
#include "3D/PieceRenderer.hpp"
#include "3D/PovCamera.hpp"
#include "3D/Skybox.hpp"
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
    void renderScene(const ChessGame& game, const ViewContext& ctx, const glm::mat4& view, const glm::mat4& proj, std::optional<Position> hoveredPos);

    std::unique_ptr<TrackballCamera> m_trackballCam;
    std::unique_ptr<PovCamera>       m_povCam;
    ICamera*                         m_activeCamera = nullptr;

    unsigned int m_fbo     = 0;
    unsigned int m_texture = 0;
    unsigned int m_rbo     = 0;

    std::unique_ptr<BoardRenderer> m_boardRenderer;
    ChessVisualState               m_visualState;

    std::unique_ptr<glimac::Program> m_program;

    std::unique_ptr<CubeMesh> m_unitCube;

    std::unique_ptr<PieceRenderer> m_pieceRenderer;
    std::unique_ptr<Skybox>        m_skyboxNight;
    std::unique_ptr<Skybox>        m_skyboxDay;

    int m_width  = 800;
    int m_height = 600;

    void resizeFBO(int width, int height);

    struct MoveAnimation {
        Position from;
        Position to;
        Piece    piece;
        float    progress = 0.0f;
    };

    std::optional<MoveAnimation> m_activeAnim;
    size_t                       m_lastHistorySize = 0;
};
