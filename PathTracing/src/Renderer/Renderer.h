#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Image.h"

namespace PathTracing
{

class Renderer
{
public:
    static void init();
    static void shutdown();

    static unsigned int getViewportWidth();
    static unsigned int getViewportHeight();

    static void begin(const glm::vec3& clearColor);
    static void pathTrace(std::shared_ptr<Image> image); // TODO : pass a scene as parameter here : "pathTrace(scene);"
    static void draw(const std::shared_ptr<Image>& image);

    static void resize(unsigned int width, unsigned int height);
};

}
