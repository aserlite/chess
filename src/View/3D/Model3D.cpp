#include "Model3D.hpp"
#include <iostream>
#include <map>
#include <tuple>

Model3D::~Model3D()
{
    cleanup();
}

Model3D::Model3D(Model3D&& other) noexcept
    : m_vao(other.m_vao), m_vbo(other.m_vbo), m_ibo(other.m_ibo), m_vertexCount(other.m_vertexCount), m_indexCount(other.m_indexCount)
{
    other.m_vao         = 0;
    other.m_vbo         = 0;
    other.m_ibo         = 0;
    other.m_vertexCount = 0;
    other.m_indexCount  = 0;
}

Model3D& Model3D::operator=(Model3D&& other) noexcept
{
    if (this != &other)
    {
        cleanup();
        m_vao         = other.m_vao;
        m_vbo         = other.m_vbo;
        m_ibo         = other.m_ibo;
        m_vertexCount = other.m_vertexCount;
        m_indexCount  = other.m_indexCount;

        other.m_vao         = 0;
        other.m_vbo         = 0;
        other.m_ibo         = 0;
        other.m_vertexCount = 0;
        other.m_indexCount  = 0;
    }
    return *this;
}

void Model3D::cleanup()
{
    if (m_vao != 0)
        glDeleteVertexArrays(1, &m_vao);
    if (m_vbo != 0)
        glDeleteBuffers(1, &m_vbo);
    if (m_ibo != 0)
        glDeleteBuffers(1, &m_ibo);
    m_vao         = 0;
    m_vbo         = 0;
    m_ibo         = 0;
    m_vertexCount = 0;
    m_indexCount  = 0;
}

bool Model3D::load(const std::string& filepath)
{
    glimac::Geometry geometry;
    bool             loaded = geometry.loadOBJ(glimac::FilePath(filepath), glimac::FilePath(filepath).dirPath(), false); // false = no textures for now

    if (!loaded)
    {
        std::cerr << "Failed to load OBJ: " << filepath << std::endl;
        return false;
    }

    std::map<std::tuple<float, float, float>, glm::vec3> posToNormal;
    
    for (size_t i = 0; i < geometry.getVertexCount(); ++i) {
        const auto& v = geometry.getVertexBuffer()[i];
        auto key = std::make_tuple(v.m_Position.x, v.m_Position.y, v.m_Position.z);
        posToNormal[key] += v.m_Normal;
    }

    glimac::Geometry::Vertex* vertices = const_cast<glimac::Geometry::Vertex*>(geometry.getVertexBuffer());
    for (size_t i = 0; i < geometry.getVertexCount(); ++i) {
        auto key = std::make_tuple(vertices[i].m_Position.x, vertices[i].m_Position.y, vertices[i].m_Position.z);
        glm::vec3 smoothed = posToNormal[key];
        if (glm::length(smoothed) > 0.0001f) {
            vertices[i].m_Normal = glm::normalize(smoothed);
        }
    }

    cleanup();

    m_vertexCount = geometry.getVertexCount();
    m_indexCount  = geometry.getIndexCount();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(glimac::Geometry::Vertex), geometry.getVertexBuffer(), GL_STATIC_DRAW);

    if (m_indexCount > 0)
    {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), geometry.getIndexBuffer(), GL_STATIC_DRAW);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*)(offsetof(glimac::Geometry::Vertex, m_Position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*)(offsetof(glimac::Geometry::Vertex, m_Normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (const GLvoid*)(offsetof(glimac::Geometry::Vertex, m_TexCoords)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (m_ibo > 0)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return true;
}

void Model3D::draw() const
{
    if (m_vao == 0)
        return;

    glBindVertexArray(m_vao);
    if (m_indexCount > 0)
    {
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    }
    glBindVertexArray(0);
}
