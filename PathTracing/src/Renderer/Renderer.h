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
    static void clear(const glm::vec3& clearColor);
};

}
