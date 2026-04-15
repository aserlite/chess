#include "ChessView3D.hpp"
#include <glad/glad.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

ChessView3D::ChessView3D() {}

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
    float vertices[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
    const char* prefixes[] = {
        "src/shaders/chess3D.",
        "../src/shaders/chess3D.",
        "../../src/shaders/chess3D."
    };

    bool loaded = false;
    for (const char* prefix : prefixes)
    {
        try
        {
            std::string vs = std::string(prefix) + "vs.glsl";
            std::string fs = std::string(prefix) + "fs.glsl";
            m_program      = std::make_unique<glimac::Program>(glimac::loadProgram(vs.c_str(), fs.c_str()));
            loaded         = true;
            break;
        }
        catch (...)
        {
            continue;
        }
    }

    if (!loaded)
    {
        std::cerr << "Impossible de charger les shaders 3D\n";
    }

    const char* asset_prefixes[] = {
        "assets/models/",
        "../assets/models/",
        "../../assets/models/"
    };

    std::string prefixToUse = "assets/models/";
    for (const char* prefix : asset_prefixes)
    {
        std::string testPath = std::string(prefix) + "pawn/pawn.obj";
        FILE*       f        = fopen(testPath.c_str(), "r");
        if (f)
        {
            fclose(f);
            prefixToUse = prefix;
            break;
        }
    }

    m_models[PieceType::Pawn].load(prefixToUse + "pawn/pawn.obj");
    m_models[PieceType::Rook].load(prefixToUse + "rook/rook.obj");
    m_models[PieceType::Knight].load(prefixToUse + "knight/knight.obj");
    m_models[PieceType::Bishop].load(prefixToUse + "bishop/bishop.obj");
    m_models[PieceType::Queen].load(prefixToUse + "queen/queen.obj");
    m_models[PieceType::King].load(prefixToUse + "king/king.obj");

    setupBuffers();
    resizeFBO(m_width, m_height);
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

void ChessView3D::draw(const ChessGame& game)
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Vue 3D");

    ImVec2 size = ImGui::GetContentRegionAvail();
    if (size.x <= 0.0f)
        size.x = 600.0f;
    if (size.y <= 0.0f)
        size.y = 600.0f;

    if (m_fbo == 0 || size.x != m_width || size.y != m_height)
    {
        resizeFBO(static_cast<int>(size.x), static_cast<int>(size.y));
    }

    if (m_fbo && size.x > 0 && size.y > 0)
    {
        GLint previous_fbo;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previous_fbo);
        GLint previous_viewport[4];
        glGetIntegerv(GL_VIEWPORT, previous_viewport);

        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        glViewport(0, 0, m_width, m_height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        if (m_program)
            m_program->use();

        float     aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
        glm::mat4 proj   = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        float camX = m_cameraDistance * std::cos(m_cameraAngleY) * std::sin(m_cameraAngleX);
        float camY = m_cameraDistance * std::sin(m_cameraAngleY);
        float camZ = m_cameraDistance * std::cos(m_cameraAngleY) * std::cos(m_cameraAngleX);

        glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        unsigned int progId            = m_program ? m_program->getGLId() : 0;
        unsigned int projLoc           = glGetUniformLocation(progId, "projection");
        unsigned int viewLoc           = glGetUniformLocation(progId, "view");
        unsigned int modelLoc          = glGetUniformLocation(progId, "model");
        unsigned int uColorOverrideLoc = glGetUniformLocation(progId, "uColorOverride");
        unsigned int uUseOverrideLoc   = glGetUniformLocation(progId, "uUseOverride");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(m_cubeVao);

        const auto& board = game.getBoard();

        glUniform3f(uColorOverrideLoc, 0.40f, 0.20f, 0.05f);
        glUniform1i(uUseOverrideLoc, 1);

        struct FramePiece {
            float x, z, sx, sz;
        };
        FramePiece frames[] = {
            {0.0f, -4.25f, 9.0f, 0.5f}, // Top
            {0.0f, 4.25f, 9.0f, 0.5f},  // Bottom
            {-4.25f, 0.0f, 0.5f, 8.0f}, // Left
            {4.25f, 0.0f, 0.5f, 8.0f}   // Right
        };

        for (const auto& f : frames)
        {
            glm::mat4 fModel = glm::translate(glm::mat4(1.0f), glm::vec3(f.x, 0.0f, f.z));
            fModel           = glm::scale(fModel, glm::vec3(f.sx, 0.2f, f.sz));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(fModel));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (int y = 0; y < 8; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                bool  isDark = (x + y) % 2 != 0;
                float color  = isDark ? 0.3f : 0.8f;

                float wx = static_cast<float>(x) - 3.5f;
                float wz = static_cast<float>(y) - 3.5f;

                glBindVertexArray(m_cubeVao);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(wx, -0.05f, wz));
                model           = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                glUniform3f(uColorOverrideLoc, color, color, color);
                glUniform1i(uUseOverrideLoc, 1);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                const Piece& p = board.getPiece(x, y);
                if (!p.isEmpty())
                {
                    float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
                    glUniform3f(uColorOverrideLoc, pr, pr, pr);

                    if (m_models.count(p.type) > 0)
                    {
                        float     scaleFactor = 0.05f;
                        glm::vec3 offset(0.0f, 0.0f, 0.0f);
                        float     rotationY = 0.0f;

                        switch (p.type)
                        {
                        case PieceType::Pawn:
                            scaleFactor = 0.1f;
                            offset      = glm::vec3(0.0f, 0.35f, 0.0f);
                            break;
                        case PieceType::Rook:
                            scaleFactor = 0.75f;
                            offset      = glm::vec3(0.0f, 0.0f, 0.0f);
                            break;
                        case PieceType::Knight:
                            scaleFactor = 0.75f;
                            offset      = glm::vec3(0.0f, 0.0f, 0.0f);
                            rotationY   = 180.0f;
                            break;
                        case PieceType::Bishop:
                            scaleFactor = 0.75f;
                            offset      = glm::vec3(0.0f, 0.0f, 0.0f);
                            break;
                        case PieceType::Queen:
                            scaleFactor = 0.75f;
                            offset      = glm::vec3(0.0f, 0.0f, 0.0f);
                            break;
                        case PieceType::King:
                            scaleFactor = 0.75f;
                            offset      = glm::vec3(0.0f, 0.0f, 0.0f);
                            break;
                        default: break;
                        }

                        glm::mat4 pModel = glm::translate(glm::mat4(1.0f), glm::vec3(wx, 0.0f, wz) + offset);
                        pModel           = glm::scale(pModel, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
                        if (rotationY != 0.0f)
                        {
                            pModel = glm::rotate(pModel, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
                        }

                        if (p.color == PieceColor::Black)
                        {
                            pModel = glm::rotate(pModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                        }

                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pModel));
                        m_models.at(p.type).draw();
                    }
                    else
                    {
                        glBindVertexArray(m_cubeVao);
                        glm::mat4 pModel = glm::translate(glm::mat4(1.0f), glm::vec3(wx, 0.35f, wz));
                        pModel           = glm::scale(pModel, glm::vec3(0.5f, 0.7f, 0.5f));
                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pModel));

                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                }
            }
        }

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);

        glBindFramebuffer(GL_FRAMEBUFFER, previous_fbo);
        glViewport(previous_viewport[0], previous_viewport[1], previous_viewport[2], previous_viewport[3]);

        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_texture)), ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::SetCursorScreenPos(pos);
        ImGui::InvisibleButton("##3DViewBtn", ImVec2(static_cast<float>(m_width), static_cast<float>(m_height)));

        if (ImGui::IsItemActive())
        {
            ImGuiIO& io = ImGui::GetIO();
            m_cameraAngleX -= io.MouseDelta.x * 0.01f;
            m_cameraAngleY -= io.MouseDelta.y * 0.01f;

            m_cameraAngleY = std::max(0.1f, std::min(1.57f, m_cameraAngleY));
        }

        if (ImGui::IsItemHovered())
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