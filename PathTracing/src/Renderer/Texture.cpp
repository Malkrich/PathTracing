#include "Texture.h"

#include <glad/glad.h>

#include "GraphicCore.h"

namespace Utils
{
    using PathTracing::ImageType;

    static GLenum getTextureInternalFormat(ImageType type)
    {
        switch (type)
        {
            case ImageType::Image32F:   return GL_RGB32F;
            case ImageType::Image32UI:  return GL_RGBA;
        }

        return 0;
    }

    static GLenum getTextureType(ImageType type)
    {
        switch (type)
        {
            case ImageType::Image32F:   return GL_FLOAT;
            case ImageType::Image32UI:  return GL_UNSIGNED_INT_8_8_8_8;
        }

        return 0;
    }
}

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
    GLenum internalFormat = Utils::getTextureInternalFormat(image->getType());
    GLenum type = Utils::getTextureType(image->getType());

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                 image->getWidth(), image->getHeight(),
                 0, GL_RGBA, type,
                 image->getData());                     CHECK_GL_ERROR();
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}



}
