#pragma once

#include "Image.h"

namespace PathTracing
{

    class Texture
    {
    public:
        Texture();
        ~Texture();

        unsigned int getTextureId() const { return m_textureId; }

        void setData(uint32_t width, uint32_t height, const void* imageData);

        void bind() const;

    private:
        unsigned int m_textureId = 0;
    };

}
