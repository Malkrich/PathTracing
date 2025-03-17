#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Image.h"

namespace PathTracing
{

    class ViewportPanel
    {
    public:
        ViewportPanel(uint32_t width, uint32_t height);

        uint32_t getWidth() const { return m_viewportTexture->getWidth(); }
        uint32_t getHeight() const { return m_viewportTexture->getHeight(); }

        void setViewportImageData(const void* imageData);

        void onGuiRender();

    private:
        std::unique_ptr<Texture> m_viewportTexture = nullptr;
    };

}
