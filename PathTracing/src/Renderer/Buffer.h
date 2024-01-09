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

    void bind() const;
    void unbind() const;

private:
    unsigned int m_bufferId;
};

}
