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
    Lambertian(glm::vec3 color_param);

    float brdf(glm::vec3 x,float theta_out,float theta_in,float lambda) const override {return 1/M_PI;};


};
}

#endif // LAMBERTIAN_H
