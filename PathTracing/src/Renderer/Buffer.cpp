#include "Buffer.h"

#include <glad/glad.h>

#include "GraphicCore.h"

namespace PathTracing
{

VertexBuffer::VertexBuffer(unsigned int size, void* data)
{
    glGenBuffers(1, &m_bufferId);                               CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);                  CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);  CHECK_GL_ERROR();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_bufferId);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); CHECK_GL_ERROR();
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_ERROR();
}




IndexBuffer::IndexBuffer(unsigned int count, void* data)
    : m_elementCount(count)
{
    glGenBuffers(1, &m_bufferId);                                       CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);                  CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW); CHECK_GL_ERROR();
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_bufferId);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); CHECK_GL_ERROR();
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECK_GL_ERROR();
}

}
