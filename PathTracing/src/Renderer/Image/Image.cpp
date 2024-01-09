#include "Image.h"


namespace PathTracing
{

Image::Image(unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
{
    m_data = new glm::vec3[width*height];

    // initializing every pixels
    for(unsigned int i = 0; i < width*height; i++)
        m_data[i] = {0.8f, 0.1f, 0.1f};
}

Image::~Image()
{
    delete[] m_data;
}

const void* Image::getBytes() const
{
    char* byteData = new char[m_width*m_height * m_channel];

    for(unsigned int i = 0; i < m_width*m_height; i++)
    {
        byteData[m_channel*i]       = char(m_data[i].r * 255.0f);
        byteData[m_channel*i + 1]   = char(m_data[i].g * 255.0f);
        byteData[m_channel*i + 2]   = char(m_data[i].b * 255.0f);
    }

    return (void*)byteData;
}

glm::vec3& Image::operator()(unsigned int x, unsigned int y)
{
    return m_data[m_width*y + x];
}

const glm::vec3& Image::operator()(unsigned int x, unsigned int y) const
{
    return m_data[m_width*y + x];
}

}
