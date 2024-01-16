#include "Light.h"

namespace PathTracing
{

Light::Light() : Material(glm::vec3(1.0,1.0,1.0))
{}

Light::Light(glm::vec3 color) : Material(color)
{}

}
