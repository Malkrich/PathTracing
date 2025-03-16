#include "Pch.h"

#include "Material.h"
#include "Renderer/PathTracing/Pdf/HittablePdf.h"
#include "Renderer/PathTracing/Pdf/CosinePdf.h"

namespace PathTracing
{

    Material::Material()
        : m_color(glm::vec3(0,0,0))
    {}

    Material::Material(const glm::vec3& color)
        : m_color(color)
    {}

}
