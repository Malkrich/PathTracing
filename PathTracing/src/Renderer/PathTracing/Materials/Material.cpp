#include "Material.h"

namespace PathTracing
{
Material::Material()
    : m_color(glm::vec3(0,0,0))
{}

Material::Material(const glm::vec3& color):
    m_color(color)
{}

}
