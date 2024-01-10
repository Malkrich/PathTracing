#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

namespace PathTracing
{
class Material {


public:
    virtual ~Material() {}

    virtual float brdf(glm::vec3 x,float theta_out,float theta_in,float lambda) const = 0;
    glm::vec3 get_albedo(glm::vec3 x,float theta_out,float theta_in,float lambda) {return color;};

private:
    glm::vec3 color;
};
}

#endif // MATERIAL_H
