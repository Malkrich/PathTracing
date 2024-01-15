#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

namespace PathTracing
{
class Material {


public:
    Material();
    Material(glm::vec3 color_param);

    virtual float brdf(glm::vec3 x,float theta_out,float theta_in,float lambda) const = 0;
    glm::vec3 get_albedo() {return color;};
    glm::vec3 get_albedo(glm::vec3 x,float theta_out,float theta_in,float lambda) {return color;};

    virtual bool CanEmit() {return false;};
    virtual glm::vec3 emitted() const {return glm::vec3(0.0f,0.0f,0.0f);};

private:
    glm::vec3 color;
};
}

#endif // MATERIAL_H
