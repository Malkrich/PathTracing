#pragma once

#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace PathTracing
{

class Screen
{
public:
    Screen(unsigned int width, unsigned int height);

    unsigned int getViewportWidth() const { return m_width; }
    unsigned int getViewportHeight() const { return m_height; }

    void clear(const glm::vec3& clearColor);
    void draw(const std::shared_ptr<Image>& image);

    void resize(unsigned int width, unsigned int height);

private:
    std::unique_ptr<Shader> m_screenShader;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    std::shared_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<Texture> m_screenTexture;

    unsigned int m_width, m_height;
};

}
