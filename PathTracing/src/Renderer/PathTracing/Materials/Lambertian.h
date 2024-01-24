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

    virtual float brdf(const glm::vec3&, float, float theta_in, float) const override
    {
        return glm::cos(theta_in) / M_PI;
    }

    virtual std::shared_ptr<Pdf> createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                           const glm::vec3& position, const glm::vec3& normal) override;
    virtual int test() const override;
};

}

#endif // LAMBERTIAN_H
