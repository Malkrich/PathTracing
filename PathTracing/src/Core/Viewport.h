#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Image.h"

namespace PathTracing
{

class Viewport
{
public:
    Viewport();

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    void setViewportImage(const std::shared_ptr<Image>& image);

    void onViewportRender();

private:
    std::unique_ptr<Texture> m_viewportTexture;
    unsigned int m_width, m_height;
};

}
