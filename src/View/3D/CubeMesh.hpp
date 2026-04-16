#pragma once
#include <glad/glad.h>

class CubeMesh {
private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;

public:
    CubeMesh();
    ~CubeMesh();

    // Prevent copying to avoid accidental OpenGL resource deletion
    CubeMesh(const CubeMesh&)            = delete;
    CubeMesh& operator=(const CubeMesh&) = delete;

    void   draw() const;
    GLuint getVao() const { return m_vao; }
};