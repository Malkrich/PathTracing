#pragma once

#include "Material.h"

#include <glm/gtc/constants.hpp>

namespace PathTracing
{

    class Lambertian : public Material
    {
    public:
        Lambertian();
        Lambertian(const glm::vec3& color);

        virtual float brdf(const glm::vec3&, float, float thetaIn, float) const override
        {
            return glm::cos(thetaIn) / glm::pi<float>();
        }

        virtual std::shared_ptr<Pdf> createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                               const glm::vec3& position, const glm::vec3& normal) override;
    };

}