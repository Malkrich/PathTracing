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

/*std::shared_ptr<Pdf> Material::createPdf(std::vector<std::shared_ptr<SceneObject>> lights,glm::vec3 position,glm::vec3 normal)
{
    std::shared_ptr<Pdf> pdf = std::make_shared<CosinePdf>(normal);
    return pdf;
}*/

}
