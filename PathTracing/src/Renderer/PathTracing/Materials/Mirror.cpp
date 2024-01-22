#include "Mirror.h"

namespace PathTracing
{

Mirror::Mirror()
    : Material()
{}

Mirror::Mirror(const glm::vec3& color)
    : Material(color)
{}

}
