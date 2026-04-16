#include "ChessView3D.hpp"
#include <glad/glad.h>
#include <glimac/glm.hpp>
#include <iostream>
#include "3D/Framebuffer.hpp"
#include "3D/MousePicker.hpp"
#include "3D/PieceRenderer.hpp"
#include "3D/SceneRenderer.hpp"
#include "3D/Skybox.hpp"
#include "3D/TrackballCamera.hpp"
#include "3D/PovCamera.hpp"
#include "Logic/Game.hpp"

ChessView3D::ChessView3D(OnMoveRequestedCb onMoveRequested)
    : m_sceneRenderer(nullptr)
    , m_framebuffer(nullptr)
    , m_mousePicker(std::make_unique<MousePicker>())
    , m_trackballCam(std::make_unique<TrackballCamera>())
    , m_povCam(std::make_unique<PovCamera>())
    , m_activeCamera(m_trackballCam.get())
    , m_onMoveRequested(std::move(onMoveRequested))
{
}

ChessView3D::~ChessView3D() = default;

void ChessView3D::init()
{
    const std::string shaderPrefix = "src/shaders/";
    const std::string assetPrefix  = "assets/";

    m_sceneRenderer = std::make_unique<SceneRenderer>(assetPrefix, shaderPrefix);
    m_framebuffer   = std::make_unique<Framebuffer>(800, 600);
}

void ChessView3D::draw(ChessGame& game, ViewContext& ctx)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
                                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | 
                                    ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("Vue 3D", nullptr, window_flags);
    ImGui::PopStyleVar();

    if (!m_sceneRenderer || !m_framebuffer)
    {
        ImGui::Text("Initialisation de la vue 3D en cours...");
        ImGui::End();
        ImGui::PopStyleVar();
        return;
    }

    drawMenuBar();

    // 1. Calculate size and layout
    ImVec2 size = ImGui::GetContentRegionAvail();
    if (size.x <= 0.0f) size.x = 600.0f;
    if (size.y <= 0.0f) size.y = 600.0f;

    m_framebuffer->resizeIfNeeded(static_cast<int>(size.x), static_cast<int>(size.y));

    // 2. Hover Calculation (Before rendering so we can pass it down)
    const ImVec2 pos = ImGui::GetCursorScreenPos();
    std::optional<Position> hoveredPos;

    if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + size.x, pos.y + size.y)))
    {
        ImVec2    mousePos(ImGui::GetMousePos());
        glm::vec2 localMousePos(mousePos.x - pos.x, mousePos.y - pos.y);
        glm::vec2 windowSize(size.x, size.y);

        hoveredPos = m_mousePicker->getBoardPosition(localMousePos, windowSize, 
                                                    m_activeCamera->getViewMatrix(), 
                                                    m_activeCamera->getProjectionMatrix(size.x, size.y));
    }

    // 3. Render
    renderPipeline(game, ctx, size, hoveredPos);

    // 4. Interaction
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_framebuffer->getTextureId())), 
                 size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::SetCursorScreenPos(pos);
    ImGui::InvisibleButton("##3DViewBtn", size);

    handleInput(game, hoveredPos, ctx);

    ImGui::End();
    ImGui::PopStyleVar();
}

void ChessView3D::renderPipeline(const ChessGame& game, const ViewContext& ctx, const ImVec2& size, const std::optional<Position>& hoveredPos)
{
    // Update camera state (e.g. following pieces)
    if (m_activeCamera == m_povCam.get())
    {
        auto activeAnim = m_visualState.getActiveAnimation();
        if (activeAnim.has_value())
        {
            m_povCam->setTargetPosition(activeAnim->getCurrentWorldPos());
            m_povCam->setMemory(activeAnim->to);
            m_povCam->setLookDirection(activeAnim->from, activeAnim->to);
        }
        else
        {
            m_povCam->setTargetFromBoardPos(ctx.selectedPos);
            if (ctx.selectedPos.x != -1)
            {
                Piece p = game.getBoard().getPiece(ctx.selectedPos.x, ctx.selectedPos.y);
                m_povCam->setTargetAngle(p.color == PieceColor::Black ? 0.0f : 3.14159265f);
            }
        }
        m_povCam->updateRotation(ImGui::GetIO().DeltaTime);
    }

    m_visualState.update(ImGui::GetIO().DeltaTime, game);

    // Bind and Draw
    GLint prev_fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_fbo);
    
    m_framebuffer->bind();
    m_framebuffer->clear(0.2f, 0.3f, 0.3f);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_sceneRenderer->drawScene(game, ctx, 
                              m_activeCamera->getViewMatrix(), 
                              m_activeCamera->getProjectionMatrix(size.x, size.y), 
                              hoveredPos, m_visualState);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    m_framebuffer->unbind();
    
    glBindFramebuffer(GL_FRAMEBUFFER, prev_fbo);
}

void ChessView3D::handleInput(const ChessGame& game, const std::optional<Position>& hoveredPos, ViewContext& ctx)
{
    if (ImGui::IsItemActive())
    {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left, 1.0f))
        {
            m_povCam->clearLookDirection();
            m_activeCamera->processMouseDrag(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
        }
    }

    if (ImGui::IsItemHovered())
    {
        m_activeCamera->processMouseScroll(ImGui::GetIO().MouseWheel);
        
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            ctx.selectedPos = {-1, -1};

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && hoveredPos)
        {
            const auto& board = game.getBoard();
            const Piece& p = board.getPiece(hoveredPos->x, hoveredPos->y);

            if (ctx.selectedPos.x == -1)
            {
                if (!p.isEmpty() && p.color == game.getCurrentTurn())
                    ctx.selectedPos = *hoveredPos;
            }
            else
            {
                if (ctx.selectedPos.x == hoveredPos->x && ctx.selectedPos.y == hoveredPos->y)
                {
                    ctx.selectedPos = {-1, -1};
                }
                else
                {
                    if (m_onMoveRequested)
                        m_onMoveRequested(ctx.selectedPos, *hoveredPos);
                    
                    // UX: Re-select if we clicked a friendly piece, otherwise clear
                    if (!p.isEmpty() && p.color == game.getCurrentTurn())
                        ctx.selectedPos = *hoveredPos;
                    else
                        ctx.selectedPos = {-1, -1};
                }
            }
        }
    }
}

void ChessView3D::drawMenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("Switch cam"))
        {
            m_activeCamera = (m_activeCamera == m_trackballCam.get()) ? (ICamera*)m_povCam.get() : (ICamera*)m_trackballCam.get();
        }
        ImGui::EndMenuBar();
    }
}