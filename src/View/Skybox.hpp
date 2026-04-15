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
    Skybox(const std::string& shaderPrefix, const std::vector<std::string>& facesPaths);
    ~Skybox();
    void render(const glm::mat4& projection, const glm::mat4& view);

private:
    unsigned int                     m_vao, m_vbo, m_textureId;
    std::unique_ptr<glimac::Program> m_program;
};