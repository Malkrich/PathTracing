#include "Image.h"


namespace PathTracing
{

Image::Image(unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
{}

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

Image32F::Image32F(unsigned int width, unsigned int height)
    : Image(width, height)
    , m_data(width * height)
{
    clearData();
}

void Image32F::clearData()
{
    for (unsigned int i = 0; i < m_data.size(); i++)
        m_data[i] = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void Image32F::resize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    m_data.resize(width * height);
    clearData();
}

void Image32F::setData(unsigned int x, unsigned int y, float r, float g, float b, float a)
{
    m_data[y * m_width + x] = { r, g, b, a };
}




Image32UI::Image32UI(unsigned int width, unsigned int height)
    : Image(width, height)
{
    m_data = new uint32_t[width * height];
    clearData();
}

Image32UI::~Image32UI()
{
    delete[] m_data;
}

void Image32UI::resize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    delete[] m_data;
    m_data = new uint32_t[width * height];

    clearData();
}

void Image32UI::setData(unsigned int x, unsigned int y, float r, float g, float b, float a)
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

void Image32UI::clearData()
{
    for (unsigned int i = 0; i < m_width * m_height; i++)
        m_data[i] = 0x000000ff;
}

}
