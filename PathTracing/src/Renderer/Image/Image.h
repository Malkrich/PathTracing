#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PathTracing
{

class Image
{
public:
    Image(unsigned int width, unsigned int height);
    ~Image();

    const void* getData() const { return glm::value_ptr(m_data[0]); }
    const void* getBytes() const;

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    glm::vec3& operator()(unsigned int x, unsigned int y);
    const glm::vec3& operator()(unsigned int x, unsigned int y) const;

private:
    const unsigned int m_channel = 3;
    unsigned int m_width, m_height;
    glm::vec3* m_data;
};

}
