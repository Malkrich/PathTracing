#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "Material.h"

namespace PathTracing
{

class Light : public Material
{
public:
    Light();
    Light(glm::vec3 color_param);

    virtual bool CanEmit() override
    {
        return true;
    }
    virtual glm::vec3 emitted() const override
    {
        //return glm::vec3(1.0f,1.0f,1.0f);
        return m_color;
    }

    virtual float brdf(const glm::vec3&, float, float, float) const override
    {
        return 0.0f;
    }

    virtual std::shared_ptr<Pdf> createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                           const glm::vec3& position, const glm::vec3& normal) override;
};

}

#endif // LIGHT_H
