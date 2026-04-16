#pragma once
#include <glad/glad.h>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

class Skybox {
public:
    Skybox(const std::string& shaderPrefix, const std::vector<std::string>& facesPaths, bool upside_down = false);
    ~Skybox();

    // copy is forbidden (because of openGL memory allocation)
    Skybox(const Skybox&)            = delete;
    Skybox& operator=(const Skybox&) = delete;

    // move is allowed explicitly
    Skybox(Skybox&&)            = default;
    Skybox& operator=(Skybox&&) = default;

    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& tint = glm::vec3(1.0f));

private:
    unsigned int                     m_vao, m_vbo, m_textureId;
    std::unique_ptr<glimac::Program> m_program;
    bool                             m_upsideDown;
};