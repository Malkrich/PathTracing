#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PathTracing
{

class Image
{
public:
    Image();
    Image(unsigned int width, unsigned int height);

    const void* getData() const { return (void*)glm::value_ptr(m_data[0]); }

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    void resize(unsigned int width, unsigned int height);

    glm::vec3& operator()(unsigned int x, unsigned int y);
    const glm::vec3& operator()(unsigned int x, unsigned int y) const;

private:
    void clearData();

private:
    unsigned int m_width, m_height;
    std::vector<glm::vec3> m_data;
};

}
