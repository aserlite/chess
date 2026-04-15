#include "ChessView3D.hpp"
#include <glad/glad.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include "PieceRenderer.hpp"
#include "Skybox.hpp"

ChessView3D::ChessView3D() = default;

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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ChessView3D::init()
{
    std::string shaderPrefixToUse = "src/shaders/";
    std::string prefixToUse       = "assets/";

    std::string vs = shaderPrefixToUse + "chess3D.vs.glsl";
    std::string fs = shaderPrefixToUse + "chess3D.fs.glsl";
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

    std::vector<std::string> faces = {
        prefixToUse + "skyboxes/night/right.png",
        prefixToUse + "skyboxes/night/left.png",
        prefixToUse + "skyboxes/night/top.png",
        prefixToUse + "skyboxes/night/bottom.png",
        prefixToUse + "skyboxes/night/front.png",
        prefixToUse + "skyboxes/night/back.png"
    };
    m_skybox = std::make_unique<Skybox>(shaderPrefixToUse, faces, true);
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

void ChessView3D::draw(const ChessGame& game, ViewContext& ctx)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Vue 3D", nullptr, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem(m_isPOV ? "Trackball cam" : "POV cam"))
        {
            m_isPOV = !m_isPOV;
        }
        ImGui::EndMenuBar();
    }

    ImVec2 size = ImGui::GetContentRegionAvail();
    if (size.x <= 0.0f)
        size.x = 600.0f;
    if (size.y <= 0.0f)
        size.y = 600.0f;

    if (m_fbo == 0 || size.x != static_cast<float>(m_width) || size.y != static_cast<float>(m_height))
    {
        resizeFBO(static_cast<int>(size.x), static_cast<int>(size.y));
    }

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

        float     aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
        glm::mat4 proj   = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        glm::mat4 view;
        if (m_isPOV)
        {
            if (ctx.selectedPos.x != -1 && ctx.selectedPos.y != -1)
            {
                ctx.lastPOVPos = ctx.selectedPos;
            }

            Position activePos = (ctx.lastPOVPos.x != -1) ? ctx.lastPOVPos : Position{3, 3};

            float px = static_cast<float>(activePos.x) - 3.5f;
            float pz = static_cast<float>(activePos.y) - 3.5f;

            glm::vec3 camPos(px, 2.0f, pz);

            float lookX = std::sin(m_povAngleX) * std::cos(m_povAngleY);
            float lookY = std::sin(m_povAngleY);
            float lookZ = std::cos(m_povAngleX) * std::cos(m_povAngleY);

            view = glm::lookAt(camPos, camPos + glm::vec3(lookX, lookY, lookZ), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else
        {
            float camX = m_cameraDistance * std::cos(m_cameraAngleY) * std::sin(m_cameraAngleX);
            float camY = m_cameraDistance * std::sin(m_cameraAngleY);
            float camZ = m_cameraDistance * std::cos(m_cameraAngleY) * std::cos(m_cameraAngleX);

            view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        unsigned int progId            = m_program ? m_program->getGLId() : 0;
        GLint        projLoc           = glGetUniformLocation(progId, "projection");
        GLint        viewLoc           = glGetUniformLocation(progId, "view");
        GLint        modelLoc          = glGetUniformLocation(progId, "model");
        GLint        uColorOverrideLoc = glGetUniformLocation(progId, "uColorOverride");
        GLint        uUseOverrideLoc   = glGetUniformLocation(progId, "uUseOverride");
        GLint        uTextureLoc       = glGetUniformLocation(progId, "uTexture");
        GLint        uHasTextureLoc    = glGetUniformLocation(progId, "uHasTexture");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(m_cubeVao);

        const auto& board = game.getBoard();

        if (m_boardRenderer)
        {
            m_boardRenderer->draw(modelLoc, uColorOverrideLoc, uUseOverrideLoc, uHasTextureLoc, uTextureLoc, m_cubeVao);
        }

        glUniform1i(uHasTextureLoc, 0);

        // Detect new moves and spawn animations
        const auto& history = game.getHistory();
        if (history.size() > m_lastHistorySize)
        {
            const auto& latest = history.back();
            if (latest.actuallyMoved && latest.from.x != -1)
            {
                MoveAnimation anim;
                anim.from     = latest.from;
                anim.to       = latest.to;
                anim.piece    = board.getPiece(latest.to.x, latest.to.y);
                anim.progress = 0.0f;
                m_activeAnim  = anim;
            }
            m_lastHistorySize = history.size();
        }
        else if (history.size() < m_lastHistorySize)
        {
            // Undo happened, cancel animation
            m_activeAnim.reset();
            m_lastHistorySize = history.size();
        }

        // Tick animation
        constexpr float animDuration = 0.4f;
        if (m_activeAnim)
        {
            m_activeAnim->progress += ImGui::GetIO().DeltaTime / animDuration;
            if (m_activeAnim->progress >= 1.0f)
            {
                m_activeAnim.reset();
            }
        }

        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                const Piece& p = board.getPiece(x, y);
                if (p.isEmpty())
                    continue;

                // If this tile is the animation destination, draw at interpolated position
                if (m_activeAnim && x == m_activeAnim->to.x && y == m_activeAnim->to.y)
                {
                    float t     = m_activeAnim->progress;
                    float fromX = static_cast<float>(m_activeAnim->from.x) - 3.5f;
                    float fromZ = static_cast<float>(m_activeAnim->from.y) - 3.5f;
                    float toX   = static_cast<float>(m_activeAnim->to.x) - 3.5f;
                    float toZ   = static_cast<float>(m_activeAnim->to.y) - 3.5f;

                    float wx = fromX + (toX - fromX) * t;
                    float wz = fromZ + (toZ - fromZ) * t;

                    float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
                    glUniform3f(uColorOverrideLoc, pr, pr, pr);

                    if (m_pieceRenderer)
                    {
                        m_pieceRenderer->draw(p, wx, wz, modelLoc, m_cubeVao);
                    }
                }
                else
                {
                    float wx = static_cast<float>(x) - 3.5f;
                    float wz = static_cast<float>(y) - 3.5f;

                    float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
                    glUniform3f(uColorOverrideLoc, pr, pr, pr);

                    if (m_pieceRenderer)
                    {
                        m_pieceRenderer->draw(p, wx, wz, modelLoc, m_cubeVao);
                    }
                }
            }
        }

        if (m_skybox)
        {
            m_skybox->render(proj, view);
        }

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);

        glBindFramebuffer(GL_FRAMEBUFFER, previous_fbo);
        glViewport(previous_viewport.at(0), previous_viewport.at(1), previous_viewport.at(2), previous_viewport.at(3));

        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_texture)), ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton("##3DViewBtn", ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)));

        if (ImGui::IsItemActive())
        {
            ImGuiIO& io = ImGui::GetIO();

            if (m_isPOV)
            {
                m_povAngleX -= io.MouseDelta.x * 0.01f;
                m_povAngleY -= io.MouseDelta.y * 0.01f;
                m_povAngleY = std::max(-1.55f, std::min(1.55f, m_povAngleY));
            }
            else
            {
                m_cameraAngleX -= io.MouseDelta.x * 0.01f;
                m_cameraAngleY -= io.MouseDelta.y * 0.01f;
                m_cameraAngleY = std::max(0.0f, std::min(1.57f, m_cameraAngleY));
            }
        }

        if (ImGui::IsItemHovered() && !m_isPOV)
        {
            ImGuiIO& io = ImGui::GetIO();
            if (io.MouseWheel != 0.0f)
            {
                m_cameraDistance -= io.MouseWheel * 1.5f;
                m_cameraDistance = std::max(2.0f, std::min(30.0f, m_cameraDistance));
            }
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}