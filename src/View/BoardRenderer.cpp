#include "BoardRenderer.hpp"
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    return textureId;
}

void BoardRenderer::draw(GLuint modelLoc, GLuint uColorOverrideLoc, GLuint uUseOverrideLoc, GLuint uHasTextureLoc, GLuint uTextureLoc, GLuint cubeVao)
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

    glUniform1i(uUseOverrideLoc, 0);
    glUniform1i(uHasTextureLoc, 1);

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            bool isDark = (x + y) % 2 != 0;

            float wx = static_cast<float>(x) - 3.5f;
            float wz = static_cast<float>(y) - 3.5f;

            glBindVertexArray(cubeVao);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(wx, -0.05f, wz));
            model           = glm::scale(model, glm::vec3(1.0f, 0.1f, 1.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            GLuint tileTex = isDark ? m_textureDarkTile : m_textureLightTile;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tileTex);
            glUniform1i(uTextureLoc, 0);
            glUniform1i(uHasTextureLoc, 1);

            glUniform3f(uColorOverrideLoc, 1.0f, 1.0f, 1.0f);
            glUniform1i(uUseOverrideLoc, 1);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}
