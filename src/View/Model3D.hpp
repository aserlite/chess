#pragma once

#include <glad/glad.h>
#include <glimac/Geometry.hpp>
#include <string>
#include <vector>

class Model3D {
public:
    Model3D() = default;
    ~Model3D();

    Model3D(const Model3D&)            = delete;
    Model3D& operator=(const Model3D&) = delete;

    Model3D(Model3D&& other) noexcept;
    Model3D& operator=(Model3D&& other) noexcept;

    bool load(const std::string& filepath);

    void draw() const;

private:
    GLuint m_vao         = 0;
    GLuint m_vbo         = 0;
    GLuint m_ibo         = 0;
    size_t m_vertexCount = 0;
    size_t m_indexCount  = 0;

    void cleanup();
};
