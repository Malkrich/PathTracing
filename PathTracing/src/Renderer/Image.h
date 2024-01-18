#pragma once

#include <cstdint>
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

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }
    glm::vec3 getPixel(unsigned int x, unsigned int y) const;
    void* getData() const { return (void*)m_data; }

    void setData(unsigned int x, unsigned int y, float r, float g, float b);
    void setData(unsigned int x, unsigned int y, const glm::vec3& color);
    void setData(unsigned int x, unsigned int y, const glm::vec4& color);
    void setData(unsigned int x, unsigned int y, float r, float g, float b, float a);

    // Interface
    void resize(unsigned int width, unsigned int height);
    void clearData();

private:
    unsigned int m_width, m_height;
    uint32_t* m_data = nullptr;
};

}
