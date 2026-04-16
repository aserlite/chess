#include "Framebuffer.hpp"
#include <iostream>
#include <utility>

Framebuffer::Framebuffer(int width, int height)
    : m_width(width)
    , m_height(height)
{
    setup();
}

Framebuffer::~Framebuffer()
{
    cleanup();
}

Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    : m_fbo(std::exchange(other.m_fbo, 0))
    , m_colorTex(std::exchange(other.m_colorTex, 0))
    , m_depthRbo(std::exchange(other.m_depthRbo, 0))
    , m_width(other.m_width)
    , m_height(other.m_height)
{
}

Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
{
    if (this != &other)
    {
        cleanup();
        m_fbo      = std::exchange(other.m_fbo, 0);
        m_colorTex = std::exchange(other.m_colorTex, 0);
        m_depthRbo = std::exchange(other.m_depthRbo, 0);
        m_width    = other.m_width;
        m_height   = other.m_height;
    }
    return *this;
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

void Framebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::resize(int width, int height)
{
    m_width  = width;
    m_height = height;

    cleanup();
    setup();
}

void Framebuffer::resizeIfNeeded(int width, int height)
{
    if (m_width == width && m_height == height)
        return;

    resize(width, height);
}

void Framebuffer::cleanup()
{
    if (m_fbo)
        glDeleteFramebuffers(1, &m_fbo);
    if (m_colorTex)
        glDeleteTextures(1, &m_colorTex);
    if (m_depthRbo)
        glDeleteRenderbuffers(1, &m_depthRbo);

    m_fbo      = 0;
    m_colorTex = 0;
    m_depthRbo = 0;
}

void Framebuffer::setup()
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Color Texture
    glGenTextures(1, &m_colorTex);
    glBindTexture(GL_TEXTURE_2D, m_colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTex, 0);

    // Depth/Stencil Renderbuffer
    glGenRenderbuffers(1, &m_depthRbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Error: Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
