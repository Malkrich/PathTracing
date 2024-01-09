#include "VertexArray.h"

#include <glad/glad.h>

#include "GraphicCore.h"

namespace PathTracing
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_arrayId);   CHECK_GL_ERROR();
}

void VertexArray::bind() const
{
    glBindVertexArray(m_arrayId); CHECK_GL_ERROR();
}

void VertexArray::unbind() const
{
    glBindVertexArray(0); CHECK_GL_ERROR();
}

void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    vertexBuffer->bind();

    // TODO : make dynamic layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);                        CHECK_GL_ERROR();
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))); CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);                                                               CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);                                                               CHECK_GL_ERROR();
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    indexBuffer->bind();
}



}
