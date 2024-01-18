#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

namespace PathTracing
{
class Material {


public:
    Material();
    Material(const glm::vec3& color);

    virtual float brdf(const glm::vec3& x,float theta_out,float theta_in,float lambda) const = 0;
    const glm::vec3& getAlbedo() const { return m_color; }
    glm::vec3& getAlbedo() { return m_color; }
    const glm::vec3& getAlbedo(const glm::vec3&, float, float, float)
    {
        return m_color;
    }

    virtual bool CanEmit() { return false; }
    virtual glm::vec3 emitted() const { return glm::vec3(0.0f,0.0f,0.0f); }

protected:
    glm::vec3 m_color;
};
}

#endif // MATERIAL_H
