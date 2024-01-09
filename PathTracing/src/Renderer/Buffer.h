#pragma once

namespace PathTracing
{

class VertexBuffer
{
public:
    VertexBuffer(unsigned int size, void* data);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

private:
    unsigned int m_bufferId;
};

class IndexBuffer
{
public:
    IndexBuffer(unsigned int count, void* data);
    ~IndexBuffer();

    unsigned int getElementCount() const { return m_elementCount; }

    void bind() const;
    void unbind() const;

private:
    unsigned int m_bufferId;

    unsigned int m_elementCount;
};

}
