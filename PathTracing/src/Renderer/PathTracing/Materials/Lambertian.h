#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <cmath>
#include "Material.h"

namespace PathTracing
{

class Lambertian : public Material
{
public:
    Lambertian();
    Lambertian(const glm::vec3& color);

    float brdf(const glm::vec3&, float, float, float) const override
    {
        return 1/M_PI;
    }

    std::shared_ptr<Pdf> createPdf(std::vector<std::shared_ptr<SceneObject>> lights,glm::vec3 position, glm::vec3 normal) override;
    int test() const override;

};

}

#endif // LAMBERTIAN_H
