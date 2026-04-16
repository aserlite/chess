#include "ChessView3D.hpp"
#include <glad/glad.h>
#include <array>
#include <glimac/glm.hpp>
#include <iostream>
#include "3D/PieceRenderer.hpp"
#include "3D/Skybox.hpp"
#include "Logic/Piece.hpp"

ChessView3D::ChessView3D()
    : m_trackballCam(std::make_unique<TrackballCamera>())
    , m_povCam(std::make_unique<PovCamera>())
    , m_activeCamera(m_trackballCam.get())
    , m_mousePicker(std::make_unique<MousePicker>())
{
}

ChessView3D::~ChessView3D()
{
    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures(1, &m_texture);
        glDeleteRenderbuffers(1, &m_rbo);
    }
}

void ChessView3D::init()
{
    const std::string shaderPrefixToUse = "src/shaders/";
    const std::string prefixToUse       = "assets/";

    const std::string vs = shaderPrefixToUse + "chess3D.vs.glsl";
    const std::string fs = shaderPrefixToUse + "chess3D.fs.glsl";
    try
    {
        m_program = std::make_unique<glimac::Program>(glimac::loadProgram(vs.c_str(), fs.c_str()));
    }
    catch (...)
    {
        std::cerr << "Impossible de charger les shaders 3D\n";
    }

    m_pieceRenderer = std::make_unique<PieceRenderer>(prefixToUse);
    m_boardRenderer = std::make_unique<BoardRenderer>(prefixToUse);

    m_unitCube = std::make_unique<CubeMesh>();

    resizeFBO(m_width, m_height);

    const std::vector<std::string> facesNight = {
        prefixToUse + "skyboxes/night/right.png",
        prefixToUse + "skyboxes/night/left.png",
        prefixToUse + "skyboxes/night/top.png",
        prefixToUse + "skyboxes/night/bottom.png",
        prefixToUse + "skyboxes/night/front.png",
        prefixToUse + "skyboxes/night/back.png"
    };
    m_skyboxNight = std::make_unique<Skybox>(shaderPrefixToUse, facesNight);

    const std::vector<std::string> facesDay = {
        prefixToUse + "skyboxes/day/right.png",
        prefixToUse + "skyboxes/day/left.png",
        prefixToUse + "skyboxes/day/top.png",
        prefixToUse + "skyboxes/day/bottom.png",
        prefixToUse + "skyboxes/day/front.png",
        prefixToUse + "skyboxes/day/back.png"
    };
    m_skyboxDay = std::make_unique<Skybox>(shaderPrefixToUse, facesDay);
}

void ChessView3D::resizeFBO(int width, int height)
{
    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures(1, &m_texture);
        glDeleteRenderbuffers(1, &m_rbo);
    }
    m_width  = width;
    m_height = height;

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ChessView3D::setupFramebuffer(const ImVec2& size)
{
    if (m_fbo == 0 || size.x != static_cast<float>(m_width) || size.y != static_cast<float>(m_height))
    {
        resizeFBO(static_cast<int>(size.x), static_cast<int>(size.y));
    }
}

void ChessView3D::renderScene(const ChessGame& game, const ViewContext& ctx, const glm::mat4& view, const glm::mat4& proj, std::optional<Position> hoveredPos)
{
    const unsigned int progId            = m_program ? m_program->getGLId() : 0;
    const GLint        projLoc           = glGetUniformLocation(progId, "projection");
    const GLint        viewLoc           = glGetUniformLocation(progId, "view");
    const GLint        modelLoc          = glGetUniformLocation(progId, "model");
    const GLint        uColorOverrideLoc = glGetUniformLocation(progId, "uColorOverride");
    const GLint        uUseOverrideLoc   = glGetUniformLocation(progId, "uUseOverride");
    const GLint        uTextureLoc       = glGetUniformLocation(progId, "uTexture");
    const GLint        uHasTextureLoc    = glGetUniformLocation(progId, "uHasTexture");
    const GLint        uOpacityLoc       = glGetUniformLocation(progId, "uOpacity");
    const GLint        uIsWhiteTurnLoc   = glGetUniformLocation(progId, "uIsWhiteTurn");

    const bool isWhiteTurn = game.getCurrentTurn() == PieceColor::White;

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniform1f(uOpacityLoc, 1.0f);
    glUniform1i(uIsWhiteTurnLoc, isWhiteTurn ? 1 : 0);

    if (m_unitCube)
        glBindVertexArray(m_unitCube->getVao());

    const auto& board = game.getBoard();

    // BOARD
    if (m_boardRenderer)
    {
        m_boardRenderer->draw(modelLoc, uColorOverrideLoc, uUseOverrideLoc, uHasTextureLoc, uTextureLoc, m_unitCube->getVao(), game, ctx, hoveredPos);
    }

    glUniform1i(uHasTextureLoc, 0);

    // PIECES
    // 1. Draw static pieces
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            const Piece& p = board.getPiece(x, y);
            if (p.isEmpty())
                continue;

            // Check if this piece is currently flying
            bool isAnimating = false;
            for (const auto& anim : m_visualState.getActiveAnimations())
            {
                if (anim.to.x == x && anim.to.y == y)
                {
                    isAnimating = true;
                    break;
                }
            }

            // If it's animating, skip it! We draw it in the next loop.
            if (isAnimating)
                continue;

            // Normal static draw
            const float wx = static_cast<float>(x) - 3.5f;
            const float wz = static_cast<float>(y) - 3.5f;
            const float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
            glUniform3f(uColorOverrideLoc, pr, pr, pr);

            bool isHoveredTarget = (ctx.selectedPos.x != -1 && hoveredPos.has_value() && hoveredPos->x == x && hoveredPos->y == y && game.isValidMove(ctx.selectedPos, {x, y}));

            if (isHoveredTarget)
            {
                glUniform1f(uOpacityLoc, 0.0f);
                glDepthMask(GL_FALSE);
            }

            if (m_pieceRenderer)
                m_pieceRenderer->draw(p, wx, wz, modelLoc, m_unitCube->getVao());

            if (isHoveredTarget)
            {
                glDepthMask(GL_TRUE);
                glUniform1f(uOpacityLoc, 1.0f);
            }
        }
    }

    // 2. Draw flying pieces
    for (const auto& anim : m_visualState.getActiveAnimations())
    {
        glm::vec3 pos = anim.getCurrentWorldPos();

        const float pr = (anim.piece.color == PieceColor::White) ? 1.0f : 0.1f;
        glUniform3f(uColorOverrideLoc, pr, pr, pr);

        if (m_pieceRenderer)
        {
            m_pieceRenderer->draw(anim.piece, pos.x, pos.z, modelLoc, m_unitCube->getVao(), pos.y);
        }
    }

    // SKYBOX
    auto& activeSkybox = isWhiteTurn ? m_skyboxDay : m_skyboxNight;
    if (activeSkybox)
    {
        // Day: warm sunlit tint. Night: cool dark blue tint.
        const glm::vec3 tint = isWhiteTurn
                                   ? glm::vec3(1.0f, 0.95f, 0.85f)  // warm day
                                   : glm::vec3(0.35f, 0.4f, 0.55f); // cold night
        activeSkybox->render(proj, view, tint);
    }

    // 3. Ghost piece (draw last with transparency)
    if (m_program)
        m_program->use();
    glBindVertexArray(m_unitCube->getVao());
    if (ctx.selectedPos.x != -1 && hoveredPos.has_value() && game.isValidMove(ctx.selectedPos, *hoveredPos))
    {
        Piece       p  = board.getPiece(ctx.selectedPos.x, ctx.selectedPos.y);
        const float wx = static_cast<float>(hoveredPos->x) - 3.5f;
        const float wz = static_cast<float>(hoveredPos->y) - 3.5f;
        const float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
        glUniform3f(uColorOverrideLoc, pr, pr, pr);

        glUniform1f(uOpacityLoc, 0.5f);
        glDepthMask(GL_FALSE);
        if (m_pieceRenderer)
            m_pieceRenderer->draw(p, wx, wz, modelLoc, m_unitCube->getVao());
        glDepthMask(GL_TRUE);
        glUniform1f(uOpacityLoc, 1.0f);
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

    if (m_fbo && size.x > 0 && size.y > 0)
    {
        GLint previous_fbo{};
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previous_fbo);
        std::array<GLint, 4> previous_viewport{};
        glGetIntegerv(GL_VIEWPORT, previous_viewport.data());

        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        glViewport(0, 0, m_width, m_height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (m_program)
            m_program->use();

        const float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
        glm::mat4   proj   = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        glm::mat4 view = m_activeCamera->getViewMatrix();

        m_visualState.update(ImGui::GetIO().DeltaTime, game);

        const ImVec2            pos = ImGui::GetCursorScreenPos();
        std::optional<Position> hoveredPos;

        if (ImGui::IsMouseHoveringRect(pos, ImVec2(pos.x + m_width, pos.y + m_height)))
        {
            ImVec2    mousePos(ImGui::GetMousePos());
            glm::vec2 localMousePos(mousePos.x - pos.x, mousePos.y - pos.y);
            glm::vec2 windowSize(static_cast<float>(m_width), static_cast<float>(m_height));

            hoveredPos = m_mousePicker->getBoardPosition(localMousePos, windowSize, view, proj);
        }

        renderScene(game, ctx, view, proj, hoveredPos);

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        glBindFramebuffer(GL_FRAMEBUFFER, previous_fbo);
        glViewport(previous_viewport.at(0), previous_viewport.at(1), previous_viewport.at(2), previous_viewport.at(3));

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_texture)), ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)), ImVec2(0, 1), ImVec2(1, 0)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)

        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton("##3DViewBtn", ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)));

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
                        ctx.selectedPos = {-1, -1};
                    else if (game.move(ctx.selectedPos, targetPos))
                        ctx.selectedPos = {-1, -1};
                    else if (!p.isEmpty() && p.color == game.getCurrentTurn())
                        ctx.selectedPos = {x, y};
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