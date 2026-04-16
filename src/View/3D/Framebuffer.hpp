#pragma once

#include <glad/glad.h>

class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    // Prevent copying
    Framebuffer(const Framebuffer&)            = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    // Allow moving
    Framebuffer(Framebuffer&& other) noexcept;
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    void bind() const;
    void unbind() const;

    void clear(float r, float g, float b, float a = 1.0f) const;
    void resize(int width, int height);
    void resizeIfNeeded(int width, int height);

    GLuint getTextureId() const { return m_colorTex; }
    int    getWidth() const { return m_width; }
    int    getHeight() const { return m_height; }

private:
    void cleanup();
    void setup();

    GLuint m_fbo      = 0;
    GLuint m_colorTex = 0;
    GLuint m_depthRbo = 0;
    int    m_width    = 0;
    int    m_height   = 0;
};
