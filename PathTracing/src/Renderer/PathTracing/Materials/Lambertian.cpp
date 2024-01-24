#include "Lambertian.h"

#include "Renderer/PathTracing/Pdf/CosinePdf.h"
#include "Renderer/PathTracing/Pdf/HittablePdf.h"
#include "Renderer/PathTracing/Pdf/MixturePdf.h"

namespace PathTracing
{

Lambertian::Lambertian()
    : Material()
{}

Lambertian::Lambertian(const glm::vec3& color)
    : Material(color)
{}

std::shared_ptr<Pdf> Lambertian::createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                           const glm::vec3& position, const glm::vec3& normal)
{
    std::vector<std::shared_ptr<Pdf>> listPdf;
    std::shared_ptr<Pdf> pdfCosine = std::make_shared<CosinePdf>(normal);
    listPdf.push_back(pdfCosine);
    for (const std::shared_ptr<SceneObject>& light : lights)
    {
        std::shared_ptr<Pdf> pdfLight = std::make_shared<HittablePdf>(*light,position,normal);
        listPdf.push_back(pdfLight);
    }
    std::shared_ptr<Pdf> pdf = std::make_shared<MixturePdf>(listPdf);
    return pdf;
}

}
