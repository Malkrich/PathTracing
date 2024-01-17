#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Image.h"
#include "PathTracing/Ray.h"
#include "Renderer/Scene/Scene.h"
#include "Renderer/Primitives/IntersectData.h"
#include "Camera.h"
#include "PathTracing/Ray.h"

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
    static void draw(const std::shared_ptr<Image>& image);

    static void resize(unsigned int width, unsigned int height);
};

}
