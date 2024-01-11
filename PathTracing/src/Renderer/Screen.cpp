#include "Screen.h"

#include <glad/glad.h>

#include "GraphicCore.h"

namespace PathTracing
{

Screen::Screen(unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
{
    m_screenShader.reset(new Shader("PathTracing/shaders/PathTracerRender.vert",
                                    "PathTracing/shaders/PathTracerRender.frag"));

    float screenPositions[] = {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                               -1.0f,  1.0f, 0.0f, 0.0f, 1.0f};

    int screenIndices[] = {0, 1, 2,
                           0, 2, 3};

    m_vertexBuffer.reset(new VertexBuffer(sizeof(screenPositions), screenPositions));
    m_indexBuffer.reset(new IndexBuffer(sizeof(screenIndices), screenIndices));
    m_vertexArray.reset(new VertexArray());
    m_vertexArray->bind();
    m_vertexArray->setVertexBuffer(m_vertexBuffer);
    m_vertexArray->setIndexBuffer(m_indexBuffer);

    m_screenTexture.reset(new Texture());
}

void Screen::clear(const glm::vec3& clearColor)
{
    /* Render here */
    glClearColor(clearColor.r,
                 clearColor.g,
                 clearColor.b,
                 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::draw(const std::shared_ptr<Image>& image)
{
    m_screenTexture->bind();
    m_screenTexture->setData(image);

    m_screenShader->bind();

    m_vertexArray->bind();

    // draw call
    glDrawElements(GL_TRIANGLES, m_vertexArray->getIndexBuffer()->getElementCount(), GL_UNSIGNED_INT, 0);    CHECK_GL_ERROR();
}

void Screen::resize(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}



}
