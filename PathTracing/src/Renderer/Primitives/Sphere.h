#ifndef Sphere_HPP
#define Sphere_HPP

#include "Primitive.h"

namespace PathTracing
{

class Sphere : public Primitive
{
public:
    Sphere(glm::vec3 const& center_param, float radius_param);

    /** Center of the Sphere */
    glm::vec3 const& center() const;
    /** Radius of the Sphere */
    float radius() const;

    /** Intersection computation with a ray */
    virtual bool intersect(Ray const& ray_param, IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_center; }
    virtual const glm::vec3& getPosition() const override { return m_center; }
    virtual void rotate(const glm::quat&) override {}

private:
    /** Center of the Sphere */
    glm::vec3 m_center;
    /** Radius of the Sphere */
    float m_radius;
};

}

#endif
