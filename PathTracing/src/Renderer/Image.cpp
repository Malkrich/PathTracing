#include "Image.h"


namespace PathTracing
{

Image::Image()
    : Image(1, 1)
{}

Image::Image(unsigned int width, unsigned int height)
    : m_width(width)
    , m_height(height)
    , m_data(width*height)
{
    clearData();
}

void Image::resize(unsigned int width, unsigned int height)
{
    m_width     = width;
    m_height    = height;
    m_data.resize(width*height);

    // reset data
    clearData();
}

glm::vec3& Image::operator()(unsigned int x, unsigned int y)
{
    return m_data[m_width*y + x];
}

void Image::clearData()
{
    // set every pixels to 0.0f
    for(unsigned int i = 0; i < m_data.size(); i++)
        m_data[i] = {0.0f, 0.0f, 0.0f};
}

const glm::vec3& Image::operator()(unsigned int x, unsigned int y) const
{
    return m_data[m_width*y + x];
}

glm::vec3& Image::operator[](unsigned int i)
{
    return m_data[i];
}

const glm::vec3& Image::operator[](unsigned int i) const
{
    return m_data[i];
}

}
