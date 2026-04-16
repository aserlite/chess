#pragma once

#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <memory>
#include <optional>
#include <string>
#include "../../Logic/Game.hpp"
#include "../ViewContext.hpp"
#include "BoardRenderer.hpp"
#include "ChessVisualState.hpp"
#include "CubeMesh.hpp"
#include "PieceRenderer.hpp"
#include "Skybox.hpp"

class SceneRenderer {
public:
    SceneRenderer(const std::string& assetPrefix, const std::string& shaderPrefix);

    void drawScene(const ChessGame& game, const ViewContext& ctx,
                   const glm::mat4& view, const glm::mat4& proj,
                   std::optional<Position> hoveredPos,
                   const ChessVisualState& visualState);

private:
    std::unique_ptr<glimac::Program> m_program;
    std::unique_ptr<PieceRenderer>   m_pieceRenderer;
    std::unique_ptr<BoardRenderer>   m_boardRenderer;
    std::unique_ptr<Skybox>          m_skyboxNight;
    std::unique_ptr<Skybox>          m_skyboxDay;
    std::unique_ptr<CubeMesh>        m_unitCube;

    // Cached uniform locations
    GLint m_projLoc           = -1;
    GLint m_viewLoc           = -1;
    GLint m_modelLoc          = -1;
    GLint m_uColorOverrideLoc = -1;
    GLint m_uUseOverrideLoc   = -1;
    GLint m_uTextureLoc       = -1;
    GLint m_uHasTextureLoc    = -1;
    GLint m_uOpacityLoc       = -1;
    GLint m_uIsWhiteTurnLoc   = -1;
};
