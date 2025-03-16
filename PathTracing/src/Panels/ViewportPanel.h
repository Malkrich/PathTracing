#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Image.h"

namespace PathTracing
{

    class ViewportPanel
    {
    public:
        ViewportPanel();

        unsigned int getWidth() const { return m_width; }
        unsigned int getHeight() const { return m_height; }

        void setViewportImageData(const void* imageData);

        void onGuiRender();

    private:
        std::unique_ptr<Texture> m_viewportTexture;
        unsigned int m_width, m_height;
    };

}
