#pragma once

#include <imgui.h>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <memory>
#include <optional>
#include "../Logic/Game.hpp"
#include "BoardRenderer.hpp"
#include "PieceRenderer.hpp"
#include "Skybox.hpp"
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
    void draw(const ChessGame& game, ViewContext& ctx);

private:
    void      setupFramebuffer(const ImVec2& size);
    glm::mat4 calculateCameraView(ViewContext& ctx) const;
    void      updateAnimations(const ChessGame& game);
    void      renderScene(const ChessGame& game, const glm::mat4& view, const glm::mat4& proj);
    void      handleCameraInput();

    unsigned int m_fbo     = 0;
    unsigned int m_texture = 0;
    unsigned int m_rbo     = 0;

    std::unique_ptr<BoardRenderer> m_boardRenderer;

    std::unique_ptr<glimac::Program> m_program;

    unsigned int m_cubeVao = 0;
    unsigned int m_cubeVbo = 0;

    std::unique_ptr<PieceRenderer> m_pieceRenderer;
    std::unique_ptr<Skybox>        m_skybox;

    int m_width  = 800;
    int m_height = 600;

    float m_cameraAngleX   = 0.0f;
    float m_cameraAngleY   = 0.8f;
    float m_cameraDistance = 10.0f;

    float m_povAngleX = 0.0f;
    float m_povAngleY = 0.0f;

    bool m_isPOV = false;

    void setupBuffers();
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
