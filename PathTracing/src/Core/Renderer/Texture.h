#pragma once

#include "Image.h"

namespace PathTracing
{

    class Texture
    {
    public:
        Texture(uint32_t width, uint32_t height);
        ~Texture();

        uint32_t getTextureId() const { return m_textureID; }
        uint32_t getWidth() const { return m_width; }
        uint32_t getHeight() const { return m_height; }

        void resize(uint32_t width, uint32_t height);

        void setData(const void* imageData);

        void bind() const;

    private:
        void invalidate();

    private:
        uint32_t m_textureID = 0;

        uint32_t m_width = 0, m_height = 0;
    };

}
