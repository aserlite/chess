#include "PieceRenderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PieceRenderer::PieceRenderer(const std::string& prefixToUse)
{
    m_models[PieceType::Pawn].load(prefixToUse + "models/pawn/pawn.obj");
    m_models[PieceType::Rook].load(prefixToUse + "models/rook/rook.obj");
    m_models[PieceType::Knight].load(prefixToUse + "models/knight/knight.obj");
    m_models[PieceType::Bishop].load(prefixToUse + "models/bishop/bishop.obj");
    m_models[PieceType::Queen].load(prefixToUse + "models/queen/queen.obj");
    m_models[PieceType::King].load(prefixToUse + "models/king/king.obj");
}

void PieceRenderer::draw(const Piece& p, float wx, float wz, GLint modelLoc, GLuint fallbackVao, float wy, const glm::mat4& danceMatrix)
{
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

        glm::mat4 pModel = glm::translate(glm::mat4(1.0f), glm::vec3(wx, wy, wz) + offset) * danceMatrix;
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
        glBindVertexArray(fallbackVao);
        glm::mat4 pModel = glm::translate(glm::mat4(1.0f), glm::vec3(wx, wy + 0.35f, wz));
        pModel           = glm::scale(pModel, glm::vec3(0.5f, 0.7f, 0.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(pModel));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
