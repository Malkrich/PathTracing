#include "Renderer.h"

#include <omp.h>

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"

#include "PathTracing/Ray.h"

#include "Scene/SceneObject.h"

#include "PathTracing/Pdf/CosinePdf.h"

namespace PathTracing
{

void Renderer::clear(const glm::vec3& clearColor)
{
    glClearColor(clearColor.r,
                 clearColor.g,
                 clearColor.b,
                 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

}
