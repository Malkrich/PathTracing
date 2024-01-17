#include "Image.h"


namespace PathTracing
{

Image::Image(unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
{
    m_data = new uint32_t[width * height];
    clearData();
}

Image::~Image()
{
    delete[] m_data;
}

void Image::setData(unsigned int x, unsigned int y, const glm::vec3& color)
{
    setData(x, y, color.r, color.g, color.b);
}

void Image::setData(unsigned int x, unsigned int y, float r, float g, float b)
{
    setData(x, y, r, g, b, 1.0f);
}

void Image::setData(unsigned int x, unsigned int y, const glm::vec4& color)
{
    setData(x, y, color.r, color.g, color.b, color.a);
}

void Image::resize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    delete[] m_data;
    m_data = new uint32_t[width * height];

    clearData();
}

void Image::setData(unsigned int x, unsigned int y, float r, float g, float b, float a)
{
    uint8_t ur = (uint8_t)(r * 255.0f);
    uint8_t ug = (uint8_t)(g * 255.0f);
    uint8_t ub = (uint8_t)(b * 255.0f);
    uint8_t ua = (uint8_t)(a * 255.0f);

    m_data[y * m_width + x] = ((uint32_t)ur << 24) 
                            | ((uint32_t)ug << 16)
                            | ((uint32_t)ub << 8)
                            | ((uint32_t)ua << 0);
}

void Image::clearData()
{
    for (unsigned int i = 0; i < m_width * m_height; i++)
        m_data[i] = 0x000000ff;
}

}
