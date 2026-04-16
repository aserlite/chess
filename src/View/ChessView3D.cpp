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
    if (m_cubeVao)
    {
        glDeleteVertexArrays(1, &m_cubeVao);
        glDeleteBuffers(1, &m_cubeVbo);
    }
}

void ChessView3D::setupBuffers()
{
    constexpr std::array<float, 288> vertices = {
        // Back face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // Bottom-right
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // Top-right
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   // Top-right
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // Top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
        // Front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // Bottom-right
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // Top-right
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // Top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
        // Left face
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top-right
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Top-left
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Bottom-right
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top-right
                                                            // Right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // Top-left
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // Top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-right
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // Bottom-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // Top-left
        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Top-right
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // Top-left
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // Bottom-left
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // Bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // Bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Top-right
        // Top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top-left
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // Top-right
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Bottom-right
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Bottom-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // Bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top-left
    };

    glGenVertexArrays(1, &m_cubeVao);
    glGenBuffers(1, &m_cubeVbo);

    glBindVertexArray(m_cubeVao);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float))); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    setupBuffers();
    resizeFBO(m_width, m_height);

    const std::vector<std::string> faces = {
        prefixToUse + "skyboxes/night/right.png",
        prefixToUse + "skyboxes/night/left.png",
        prefixToUse + "skyboxes/night/top.png",
        prefixToUse + "skyboxes/night/bottom.png",
        prefixToUse + "skyboxes/night/front.png",
        prefixToUse + "skyboxes/night/back.png"
    };
    m_skybox = std::make_unique<Skybox>(shaderPrefixToUse, faces);
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

void ChessView3D::renderScene(const ChessGame& game, const glm::mat4& view, const glm::mat4& proj)
{
    const unsigned int progId            = m_program ? m_program->getGLId() : 0;
    const GLint        projLoc           = glGetUniformLocation(progId, "projection");
    const GLint        viewLoc           = glGetUniformLocation(progId, "view");
    const GLint        modelLoc          = glGetUniformLocation(progId, "model");
    const GLint        uColorOverrideLoc = glGetUniformLocation(progId, "uColorOverride");
    const GLint        uUseOverrideLoc   = glGetUniformLocation(progId, "uUseOverride");
    const GLint        uTextureLoc       = glGetUniformLocation(progId, "uTexture");
    const GLint        uHasTextureLoc    = glGetUniformLocation(progId, "uHasTexture");

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glBindVertexArray(m_cubeVao);

    const auto& board = game.getBoard();

    // BOARD
    if (m_boardRenderer)
    {
        m_boardRenderer->draw(modelLoc, uColorOverrideLoc, uUseOverrideLoc, uHasTextureLoc, uTextureLoc, m_cubeVao);
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

            if (m_pieceRenderer)
                m_pieceRenderer->draw(p, wx, wz, modelLoc, m_cubeVao);
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
            m_pieceRenderer->draw(anim.piece, pos.x, pos.z, modelLoc, m_cubeVao, pos.y);
        }
    }

    // SKYBOX
    if (m_skybox)
    {
        m_skybox->render(proj, view);
    }
}

void ChessView3D::draw(const ChessGame& game, ViewContext& ctx)
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

        if (m_program)
            m_program->use();

        const float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
        glm::mat4   proj   = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        glm::mat4 view = m_activeCamera->getViewMatrix();

        m_visualState.update(ImGui::GetIO().DeltaTime, game);

        renderScene(game, view, proj);

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);

        glBindFramebuffer(GL_FRAMEBUFFER, previous_fbo);
        glViewport(previous_viewport.at(0), previous_viewport.at(1), previous_viewport.at(2), previous_viewport.at(3));

        const ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_texture)), ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)), ImVec2(0, 1), ImVec2(1, 0)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)

        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton("##3DViewBtn", ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)));

        if (ImGui::IsItemActive())
        {
            m_povCam->clearLookDirection();
            m_activeCamera->processMouseDrag(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
        }
        if (ImGui::IsItemHovered())
        {
            m_activeCamera->processMouseScroll(ImGui::GetIO().MouseWheel);
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}