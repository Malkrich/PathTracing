#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Renderer/PathTracing/Pdf/Pdf.h"

namespace PathTracing
{

struct SceneObject;

class Material
{
public:
    Material();
    Material(const glm::vec3& color);

    virtual float brdf(const glm::vec3& x, float thetaOut, float thetaIn, float lambda) const = 0;
    virtual const glm::vec3& getAlbedo() const { return m_color; }
    virtual glm::vec3& getAlbedo() { return m_color; }
    virtual const glm::vec3& getAlbedo(const glm::vec3&, float, float, float)
    {
        return m_color;
    }
    virtual std::shared_ptr<Pdf> createPdf(const std::vector<std::shared_ptr<SceneObject>>& lights,
                                           const glm::vec3& position, const glm::vec3& normal) = 0;
    virtual int test() const { return 2; }

    virtual bool CanEmit() { return false; }
    virtual glm::vec3 emitted() const { return glm::vec3(0.0f,0.0f,0.0f); }

protected:
    glm::vec3 m_color;
};

}

#endif // MATERIAL_H
