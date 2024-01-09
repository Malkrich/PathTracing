#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Buffer.h"
#include "VertexArray.h"
#include "Image.h"

namespace PathTracing
{

class Renderer
{
public:
    Renderer();

    void begin(const glm::vec3& clearColor) const;
    void draw();

private:
    void initialize();

private:
    unsigned int m_screenProgramId;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
    std::shared_ptr<VertexArray> m_vertexArray;
    unsigned int m_screenTextureId;

    Image m_screenImage;
};

}
