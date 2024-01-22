#ifndef MIRROR_H
#define MIRROR_H

#include "Material.h"

namespace PathTracing
{
class Mirror : public Material
{
public:
    Mirror();
    Mirror(const glm::vec3& color);
    float brdf(const glm::vec3&, float, float, float) const override
    {
        return 1;
    }

    const glm::vec3& getAlbedo() const override { return glm::vec3(1,1,1); }
    const glm::vec3& getAlbedo(const glm::vec3&, float, float, float) override
    {
        return glm::vec3(1,1,1);
    }

};
}

#endif // MIRROR_H
