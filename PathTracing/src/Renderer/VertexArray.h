#pragma once

#include <memory>

#include "Buffer.h"

namespace PathTracing
{

class VertexArray
{
public:
    VertexArray();

    void bind() const;
    void unbind() const;

    const std::shared_ptr<VertexBuffer>& getVertexBuffer() const { return m_vertexBuffer; }
    const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_indexBuffer; }

    void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

private:
    unsigned int m_arrayId;

    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

}
