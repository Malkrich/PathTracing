#include "Pch.h"

#include "Texture.h"
#include "GraphicCore.h"

#include <glad/glad.h>

namespace PathTracing
{

    Texture::Texture(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {
        invalidate();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_textureID);
    }

    void Texture::resize(uint32_t width, uint32_t height)
    {
        if (m_width == width && m_height == height)
            return;

        m_width = width;
        m_height = height;

        invalidate();
    }

    void Texture::setData(const void* imageData)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, imageData);
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture::invalidate()
    {
        if (m_textureID)
        {
            glDeleteTextures(1, &m_textureID);
            m_textureID = 0;
        }

        // Create texture
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // Generate texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, nullptr);

        // Set filters and wrapping mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);

        CHECK_GL_ERROR();
    }

}
