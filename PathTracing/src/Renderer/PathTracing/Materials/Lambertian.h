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

};

}

#endif // LAMBERTIAN_H
