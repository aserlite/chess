#include "BoardRenderer.hpp"
#include "VictoryAnimator.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

BoardRenderer::BoardRenderer(const std::string& prefixToUse)
{
    m_textureLightTile = loadTexture(prefixToUse + "textures/white.png");
    m_textureDarkTile  = loadTexture(prefixToUse + "textures/black.png");
}

BoardRenderer::~BoardRenderer()
{
    if (m_textureLightTile)
        glDeleteTextures(1, &m_textureLightTile);
    if (m_textureDarkTile)
        glDeleteTextures(1, &m_textureDarkTile);
}

GLuint BoardRenderer::loadTexture(const std::string& path)
{
    GLuint textureId = 0;
    auto img = glimac::loadImage(path);
    if (img)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(img->getWidth()), static_cast<GLsizei>(img->getHeight()), 0, GL_RGBA, GL_FLOAT, img->getPixels());
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    return textureId;
}

void BoardRenderer::draw(GLint modelLoc, GLint uColorOverrideLoc, GLint uUseOverrideLoc, GLint uHasTextureLoc, GLint uTextureLoc, GLuint cubeVao, const ChessGame& game, const ViewContext& ctx, std::optional<Position> hoveredPos, const VictoryAnimator* va)
{
    glBindVertexArray(cubeVao);

    glUniform3f(uColorOverrideLoc, 0.40f, 0.20f, 0.05f);
    glUniform1i(uUseOverrideLoc, 1);
    glUniform1i(uHasTextureLoc, 0);

    struct FramePiece {
        float x, z, sx, sz;
    };
    constexpr std::array<FramePiece, 4> frames = {{
        {0.0f, -4.25f, 9.0f, 0.5f}, 
        {0.0f, 4.25f, 9.0f, 0.5f},  
        {-4.25f, 0.0f, 0.5f, 8.0f}, 
        {4.25f, 0.0f, 0.5f, 8.0f}   
    }};

    for (const auto& f : frames)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(f.x, -0.2f, f.z));
        model           = glm::scale(model, glm::vec3(f.sx, 0.5f, f.sz));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            const bool isDark = (x + y) % 2 != 0;

            const float wx = static_cast<float>(x) - 3.5f;
            const float wz = static_cast<float>(y) - 3.5f;

            glBindVertexArray(cubeVao);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(wx, -0.05f, wz));
            model           = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            const GLuint tileTex = isDark ? m_textureDarkTile : m_textureLightTile;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tileTex);
            glUniform1i(uTextureLoc, 0);
            glUniform1i(uHasTextureLoc, 1);

            if (ctx.selectedPos.x == x && ctx.selectedPos.y == y)
                glUniform3f(uColorOverrideLoc, 0.0f, 0.8f, 0.0f); // Selected: Green
            else if (ctx.selectedPos.x != -1 && game.isValidMove(ctx.selectedPos, {x, y}))
                glUniform3f(uColorOverrideLoc, 0.2f, 0.5f, 1.0f); // Valid move: Blueish
            else if (hoveredPos && hoveredPos->x == x && hoveredPos->y == y)
                glUniform3f(uColorOverrideLoc, 1.2f, 1.2f, 0.8f); // Hovered: Brighter yellow tinted
            else
                glUniform3f(uColorOverrideLoc, 1.0f, 1.0f, 1.0f); // normal

            if (va && va->isActive())
            {
                const glm::vec3 dc = va->getDiscoColor(static_cast<float>(x + y) * 0.09f);
                glUniform3f(uColorOverrideLoc, dc.r, dc.g, dc.b);
            }

            glUniform1i(uUseOverrideLoc, 1);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}
