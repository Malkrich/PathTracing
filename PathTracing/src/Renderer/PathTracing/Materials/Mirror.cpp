#include "Mirror.h"
#include "Renderer/PathTracing/Pdf/MirrorPdf.h"

namespace PathTracing
{

Mirror::Mirror()
    : Material()
{}

Mirror::Mirror(const glm::vec3& color)
    : Material(color)
{}

std::shared_ptr<Pdf> Mirror::createPdf(const std::vector<std::shared_ptr<SceneObject>>&,
                                       const glm::vec3&, const glm::vec3& normal)
{
    std::shared_ptr<Pdf> pdf = std::make_shared<MirrorPdf>(normal);
    return pdf;
}

}
