#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace PathTracing
{

class Renderer
{
public:
    static void init();
    static void shutdown();

    static void begin(const glm::vec3& clearColor);
    static void pathTrace(); // TODO : pass a scene as parameter here : "pathTrace(scene);"
    static void draw();

    static void resize(unsigned int width, unsigned int height);
};

}
