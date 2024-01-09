#include "Texture.h"

#include <glad/glad.h>

#include "GraphicCore.h"

namespace PathTracing
{

Texture::Texture()
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::setData(const std::shared_ptr<Image>& image)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F,
                 image->getWidth(), image->getHeight(),
                 0, GL_RGB,  GL_FLOAT,
                 image->getData());                     CHECK_GL_ERROR();
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}



}
