#pragma once

#include <memory>

#include "Image.h"

namespace PathTracing
{

class Texture
{
public:
    Texture();

    void setData(const std::shared_ptr<Image>& image);

    void bind() const;

private:
    unsigned int m_textureId;
};

}
