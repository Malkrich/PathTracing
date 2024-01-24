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

    virtual float brdf(const glm::vec3&, float, float, float) const override
    {
        return 1.0f;
    }

//    const glm::vec3& getAlbedo() const override { return glm::vec3(1,1,1); }
//    const glm::vec3& getAlbedo(const glm::vec3&, float, float, float) override
//    {
//        return glm::vec3(1,1,1);
//    }
    virtual std::shared_ptr<Pdf> createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                   const glm::vec3& position, const glm::vec3& normal) override;
    virtual int test() const override;
};

}

#endif // MIRROR_H
