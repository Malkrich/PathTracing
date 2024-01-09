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

    void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

private:
    unsigned int m_arrayId;
};

}
