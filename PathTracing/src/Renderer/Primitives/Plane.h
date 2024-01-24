#include "Primitive.h"

#ifndef PLANE_H
#define PLANE_H

namespace PathTracing
{

class Plane : public Primitive
{
public:
    Plane(glm::vec3 const& position, glm::vec3 const& normal);

    /*Return normal of the plane*/
    glm::vec3 const& getNormal() const { return m_normal; }

    virtual bool intersect(Ray const& ray_param, IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_position; }
    virtual const glm::vec3& getPosition() const override { return m_position; }
    virtual void rotate(const glm::quat&) override {}

private:
    glm::vec3 m_position;
    glm::vec3 m_normal;
};

}



#endif // PLANE_H
