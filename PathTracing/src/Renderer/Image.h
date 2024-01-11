#pragma once

#include <cstdint>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PathTracing
{

enum class ImageType
{
    Image32F, Image32UI
};

class Image
{
public:
    Image(unsigned int width, unsigned int height);
    virtual ~Image() {}

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    void setData(unsigned int x, unsigned int y, float r, float g, float b);
    void setData(unsigned int x, unsigned int y, const glm::vec3& color);
    void setData(unsigned int x, unsigned int y, const glm::vec4& color);

    // Interface
    virtual inline ImageType getType() const = 0;
    virtual void resize(unsigned int width, unsigned int height) = 0;
    virtual const void* getData() const = 0;
    virtual void setData(unsigned int x, unsigned int y, float r, float g, float b, float a) = 0;

protected:
    unsigned int m_width, m_height;
};

class Image32F : public Image
{
public:
    Image32F(unsigned int width, unsigned int height);

    virtual inline ImageType getType() const override { return ImageType::Image32F; }
    virtual void resize(unsigned int width, unsigned int height) override;
    virtual const void* getData() const override
    {
        return (void*)glm::value_ptr(m_data[0]);
    }
    virtual void setData(unsigned int x, unsigned int y, float r, float g, float b, float a) override;

private:
    void clearData();

private:
    std::vector<glm::vec4> m_data;
};

class Image32UI : public Image
{
public:
    Image32UI(unsigned int width, unsigned int height);
    virtual ~Image32UI();

    virtual inline ImageType getType() const override { return ImageType::Image32UI; }
    virtual void resize(unsigned int width, unsigned int height) override;
    virtual const void* getData() const override
    {
        return (void*)m_data;
    }
    virtual void setData(unsigned int x, unsigned int y, float r, float g, float b, float a) override;

private:
    void clearData();

private:
    uint32_t* m_data = nullptr;
};

}
