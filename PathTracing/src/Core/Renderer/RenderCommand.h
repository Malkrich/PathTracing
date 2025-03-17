#pragma once

#include <glm/glm.hpp>

namespace PathTracing
{

    class RenderCommand
    {
    public:
        static void clear(const glm::vec3& clearColor);
    };

}
