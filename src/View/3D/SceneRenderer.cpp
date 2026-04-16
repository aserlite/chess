#include "SceneRenderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

SceneRenderer::SceneRenderer(const std::string& assetPrefix, const std::string& shaderPrefix)
{
    const std::string vs = shaderPrefix + "chess3D.vs.glsl";
    const std::string fs = shaderPrefix + "chess3D.fs.glsl";

    try
    {
        m_program = std::make_unique<glimac::Program>(glimac::loadProgram(vs.c_str(), fs.c_str()));
    }
    catch (...)
    {
        std::cerr << "Impossible de charger les shaders 3D\n";
    }

    if (m_program)
    {
        const unsigned int progId = m_program->getGLId();
        m_projLoc                 = glGetUniformLocation(progId, "projection");
        m_viewLoc                 = glGetUniformLocation(progId, "view");
        m_modelLoc                = glGetUniformLocation(progId, "model");
        m_uColorOverrideLoc       = glGetUniformLocation(progId, "uColorOverride");
        m_uUseOverrideLoc         = glGetUniformLocation(progId, "uUseOverride");
        m_uTextureLoc             = glGetUniformLocation(progId, "uTexture");
        m_uHasTextureLoc          = glGetUniformLocation(progId, "uHasTexture");
        m_uOpacityLoc             = glGetUniformLocation(progId, "uOpacity");
        m_uIsWhiteTurnLoc         = glGetUniformLocation(progId, "uIsWhiteTurn");
    }

    m_pieceRenderer = std::make_unique<PieceRenderer>(assetPrefix);
    m_boardRenderer = std::make_unique<BoardRenderer>(assetPrefix);
    m_unitCube      = std::make_unique<CubeMesh>();

    const std::vector<std::string> facesNight = {
        assetPrefix + "skyboxes/night/right.png",
        assetPrefix + "skyboxes/night/left.png",
        assetPrefix + "skyboxes/night/top.png",
        assetPrefix + "skyboxes/night/bottom.png",
        assetPrefix + "skyboxes/night/front.png",
        assetPrefix + "skyboxes/night/back.png"};
    m_skyboxNight = std::make_unique<Skybox>(shaderPrefix, facesNight);

    const std::vector<std::string> facesDay = {
        assetPrefix + "skyboxes/day/right.png",
        assetPrefix + "skyboxes/day/left.png",
        assetPrefix + "skyboxes/day/top.png",
        assetPrefix + "skyboxes/day/bottom.png",
        assetPrefix + "skyboxes/day/front.png",
        assetPrefix + "skyboxes/day/back.png"};
    m_skyboxDay = std::make_unique<Skybox>(shaderPrefix, facesDay);
}

void SceneRenderer::drawScene(const ChessGame& game, const ViewContext& ctx,
                             const glm::mat4& view, const glm::mat4& proj,
                             std::optional<Position> hoveredPos,
                             const ChessVisualState& visualState)
{
    if (m_program)
        m_program->use();

    const bool isWhiteTurn = game.getCurrentTurn() == PieceColor::White;

    glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniform1f(m_uOpacityLoc, 1.0f);
    glUniform1i(m_uIsWhiteTurnLoc, isWhiteTurn ? 1 : 0);

    const GLuint cubeVao = m_unitCube ? m_unitCube->getVao() : 0;
    if (cubeVao)
        glBindVertexArray(cubeVao);

    const auto& board = game.getBoard();
    const VictoryAnimator& va = visualState.getVictoryAnimator();

    // BOARD
    if (m_boardRenderer)
    {
        m_boardRenderer->draw(m_modelLoc, m_uColorOverrideLoc, m_uUseOverrideLoc, m_uHasTextureLoc, m_uTextureLoc, cubeVao, game, ctx, hoveredPos, &va);
    }

    glUniform1i(m_uHasTextureLoc, 0);

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
            for (const auto& anim : visualState.getActiveAnimations())
            {
                if (anim.to.x == x && anim.to.y == y)
                {
                    isAnimating = true;
                    break;
                }
            }

            if (isAnimating)
                continue;

            // Normal static draw
            const float wx = static_cast<float>(x) - 3.5f;
            const float wz = static_cast<float>(y) - 3.5f;

            if (va.isWinnerPiece(p.color))
            {
                const float     phase = wx * 0.1f + wz * 0.07f;
                const glm::vec3 dc    = va.getDiscoColor(phase);
                glUniform3f(m_uColorOverrideLoc, dc.r, dc.g, dc.b);
            }
            else
            {
                const float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
                glUniform3f(m_uColorOverrideLoc, pr, pr, pr);
            }

            bool isHoveredTarget = (ctx.selectedPos.x != -1 && hoveredPos.has_value() && hoveredPos->x == x && hoveredPos->y == y && game.isValidMove(ctx.selectedPos, {x, y}));

            if (isHoveredTarget)
            {
                glUniform1f(m_uOpacityLoc, 0.0f);
                glDepthMask(GL_FALSE);
            }

            const glm::mat4 dance = va.isWinnerPiece(p.color)
                                        ? va.getDanceMatrix(wx, wz)
                                        : glm::mat4(1.0f);

            if (m_pieceRenderer)
                m_pieceRenderer->draw(p, wx, wz, m_modelLoc, cubeVao, 0.0f, dance);

            if (isHoveredTarget)
            {
                glDepthMask(GL_TRUE);
                glUniform1f(m_uOpacityLoc, 1.0f);
            }
        }
    }

    // 2. Draw flying pieces
    for (const auto& anim : visualState.getActiveAnimations())
    {
        glm::vec3 pos = anim.getCurrentWorldPos();

        const float pr = (anim.piece.color == PieceColor::White) ? 1.0f : 0.1f;
        glUniform3f(m_uColorOverrideLoc, pr, pr, pr);

        if (m_pieceRenderer)
        {
            m_pieceRenderer->draw(anim.piece, pos.x, pos.z, m_modelLoc, cubeVao, pos.y);
        }
    }

    // SKYBOX
    auto& activeSkybox = isWhiteTurn ? m_skyboxDay : m_skyboxNight;
    if (activeSkybox)
    {
        const glm::vec3 tint = isWhiteTurn
                                   ? glm::vec3(1.0f, 0.95f, 0.85f)  // warm day
                                   : glm::vec3(0.35f, 0.4f, 0.55f); // cold night
        activeSkybox->render(proj, view, tint);
    }

    // 3. Ghost piece (draw last with transparency)
    if (m_program)
        m_program->use();
    if (cubeVao)
        glBindVertexArray(cubeVao);
    if (ctx.selectedPos.x != -1 && hoveredPos.has_value() && game.isValidMove(ctx.selectedPos, *hoveredPos))
    {
        Piece       p  = board.getPiece(ctx.selectedPos.x, ctx.selectedPos.y);
        const float wx = static_cast<float>(hoveredPos->x) - 3.5f;
        const float wz = static_cast<float>(hoveredPos->y) - 3.5f;
        const float pr = (p.color == PieceColor::White) ? 1.0f : 0.1f;
        glUniform3f(m_uColorOverrideLoc, pr, pr, pr);

        glUniform1f(m_uOpacityLoc, 0.5f);
        glDepthMask(GL_FALSE);
        if (m_pieceRenderer)
            m_pieceRenderer->draw(p, wx, wz, m_modelLoc, cubeVao);
        glDepthMask(GL_TRUE);
        glUniform1f(m_uOpacityLoc, 1.0f);
    }
}
