#ifndef HITTABLEPDF_H
#define HITTABLEPDF_H

#include <glm/glm.hpp>

#include "Pdf.h"
#include "Renderer/Scene/SceneObject.h"

namespace PathTracing
{

class HittablePdf : public Pdf
{
public:
    HittablePdf(const SceneObject& obj, const glm::vec3& origin, const glm::vec3& normal)
        : m_objects(obj)
        , m_origin(origin)
        , m_normal(normal)
    {}

    virtual double value(const glm::vec3& direction) const override
    {
        return m_objects.pdf_value(m_origin, m_normal, direction);
    }

    virtual glm::vec3 generate(const Ray&) const override
    {
        return m_objects.random(m_origin);
    }

private:
    const SceneObject m_objects; //Objet que l'on vise, par exemple la lumiere
    glm::vec3 m_origin; //Point de l'intersection (pas la lumiere)
    glm::vec3 m_normal; //Normal de l'intersection (pas la lumiere)
};


}

#endif // HITTABLEPDF_H
