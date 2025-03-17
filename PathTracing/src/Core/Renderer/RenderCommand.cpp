#include "Pch.h"

#include "RenderCommand.h"

#include <glad/glad.h>

namespace PathTracing
{

    void RenderCommand::clear(const glm::vec3& clearColor)
    {
        glClearColor(clearColor.r,
                     clearColor.g,
                     clearColor.b,
                     1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

}
