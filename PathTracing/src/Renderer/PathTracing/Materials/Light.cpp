#include "Light.h"
#include "Renderer/PathTracing/Pdf/CosinePdf.h"

namespace PathTracing
{

Light::Light() : Material(glm::vec3(1.0,1.0,1.0))
{}

Light::Light(glm::vec3 color) : Material(color)
{}

std::shared_ptr<Pdf> Light::createPdf(const std::vector<std::shared_ptr<SceneObject>>&,
                                      const glm::vec3&, const glm::vec3& normal)
{
    std::shared_ptr<Pdf> pdf = std::make_shared<CosinePdf>(normal);
    return pdf;
}

}
