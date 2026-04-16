#include "ChessView3D.hpp"
#include <glad/glad.h>
#include <array>
#include <glimac/glm.hpp>
#include <iostream>
#include "3D/Framebuffer.hpp"
#include "3D/PieceRenderer.hpp"
#include "3D/Skybox.hpp"
#include "Logic/Piece.hpp"

ChessView3D::ChessView3D(OnMoveRequestedCb onMoveRequested)
    : m_onMoveRequested(std::move(onMoveRequested))
    , m_trackballCam(std::make_unique<TrackballCamera>())
    , m_povCam(std::make_unique<PovCamera>())
    , m_activeCamera(m_trackballCam.get())
    , m_mousePicker(std::make_unique<MousePicker>())
{
}

ChessView3D::~ChessView3D()
{
}

void ChessView3D::init()
{
    const std::string shaderPrefixToUse = "src/shaders/";
    const std::string prefixToUse       = "assets/";

    m_sceneRenderer = std::make_unique<SceneRenderer>(prefixToUse, shaderPrefixToUse);
    m_framebuffer   = std::make_unique<Framebuffer>(800, 600);
}

void ChessView3D::setupFramebuffer(const ImVec2& size)
{
    if (m_framebuffer)
    {
        m_framebuffer->resize(static_cast<int>(size.x), static_cast<int>(size.y));
    }
}

void ChessView3D::draw(ChessGame& game, ViewContext& ctx)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    // 2. Set the next window position and size to match the viewport
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    // 3. Set flags to make it feel like a background layer (no title bar, no resize, etc.)
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // 4. Start the window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // Make corners sharp
    ImGui::Begin("Vue 3D", nullptr, window_flags);
    ImGui::PopStyleVar();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("Switch cam"))
        {
            if (m_activeCamera == m_trackballCam.get())
            {
                m_activeCamera = m_povCam.get();
            }
            else
            {
                m_activeCamera = m_trackballCam.get();
            }
        }
    }
    ImGui::EndMenuBar();

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
            const auto& board = game.getBoard();
            if (ctx.selectedPos.x != -1)
            {
                Piece p = board.getPiece(ctx.selectedPos.x, ctx.selectedPos.y);
                m_povCam->setTargetAngle(p.color == PieceColor::Black ? 0.0f : 3.14159265f);
            }
        }

        m_povCam->updateRotation(ImGui::GetIO().DeltaTime);
    }

    ImVec2 size = ImGui::GetContentRegionAvail();
    if (size.x <= 0.0f)
        size.x = 600.0f;
    if (size.y <= 0.0f)
        size.y = 600.0f;

    setupFramebuffer(size);

    if (m_framebuffer && size.x > 0 && size.y > 0)
    {
        GLint previous_fbo{};
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previous_fbo);
        std::array<GLint, 4> previous_viewport{};
        glGetIntegerv(GL_VIEWPORT, previous_viewport.data());

        m_framebuffer->bind();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        const float aspect = static_cast<float>(m_framebuffer->getWidth()) / static_cast<float>(m_framebuffer->getHeight());
        glm::mat4   proj   = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        glm::mat4 view = m_activeCamera->getViewMatrix();

        m_visualState.update(ImGui::GetIO().DeltaTime, game);

        const ImVec2            pos = ImGui::GetCursorScreenPos();
        std::optional<Position> hoveredPos;

        if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + m_framebuffer->getWidth(), pos.y + m_framebuffer->getHeight())))
        {
            ImVec2    mousePos(ImGui::GetMousePos());
            glm::vec2 localMousePos(mousePos.x - pos.x, mousePos.y - pos.y);
            glm::vec2 windowSize(static_cast<float>(m_framebuffer->getWidth()), static_cast<float>(m_framebuffer->getHeight()));

            hoveredPos = m_mousePicker->getBoardPosition(localMousePos, windowSize, view, proj);
        }

        if (m_sceneRenderer)
        {
            m_sceneRenderer->drawScene(game, ctx, view, proj, hoveredPos, m_visualState);
        }

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        glBindFramebuffer(GL_FRAMEBUFFER, previous_fbo);
        glViewport(previous_viewport.at(0), previous_viewport.at(1), previous_viewport.at(2), previous_viewport.at(3));

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_framebuffer->getTextureId())), ImVec2(static_cast<float>(m_framebuffer->getWidth()), static_cast<float>(m_framebuffer->getHeight())), ImVec2(0, 1), ImVec2(1, 0)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)

        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton("##3DViewBtn", ImVec2(static_cast<float>(m_framebuffer->getWidth()), static_cast<float>(m_framebuffer->getHeight())));

        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 1.0f))
        {
            m_povCam->clearLookDirection();
            m_activeCamera->processMouseDrag(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
        }

        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            if (hoveredPos)
            {
                int          x     = hoveredPos->x;
                int          y     = hoveredPos->y;
                const auto&  board = game.getBoard();
                const Piece& p     = board.getPiece(x, y);

                if (ctx.selectedPos.x == -1)
                {
                    if (!p.isEmpty() && p.color == game.getCurrentTurn())
                        ctx.selectedPos = {x, y};
                }
                else
                {
                    Position targetPos = {x, y};
                    if (ctx.selectedPos.x == x && ctx.selectedPos.y == y)
                    {
                        ctx.selectedPos = {-1, -1};
                    }
                    else
                    {
                        if (m_onMoveRequested)
                            m_onMoveRequested(ctx.selectedPos, targetPos);

                        // If the move was invalid or if we clicked a new piece,
                        // handle the selection logic (the move request is handled by the orchestrator)
                        if (!p.isEmpty() && p.color == game.getCurrentTurn())
                            ctx.selectedPos = {x, y};
                        else
                            ctx.selectedPos = {-1, -1};
                    }
                }
            }
        }

        if (ImGui::IsItemHovered())
        {
            m_activeCamera->processMouseScroll(ImGui::GetIO().MouseWheel);
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                ctx.selectedPos = {-1, -1};
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}