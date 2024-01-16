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

    bool CanEmit() override
    {
        return true;
    }
    glm::vec3 emitted() const override
    {
        return glm::vec3(1.0f,1.0f,1.0f);
    }

    float brdf(const glm::vec3&, float, float, float) const override
    {
        return 0.0f;
    }

};

}

#endif // LIGHT_H
