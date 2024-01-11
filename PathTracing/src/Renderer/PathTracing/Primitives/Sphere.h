#ifndef Sphere_HPP
#define Sphere_HPP

#include "Primitive.h"

namespace PathTracing
{

class Sphere : public Primitive
{
public:

    Sphere(glm::vec3 const& center_param,float radius_param);

    /** Center of the Sphere */
    glm::vec3 const& center() const;
    /** Radius of the Sphere */
    float radius() const;

    /** Intersection computation with a ray */
    bool intersect(Ray const& ray_param,IntersectData& intersection) const override;



private:

    /** Center of the Sphere */
    glm::vec3 center_data;
    /** Radius of the Sphere */
    float radius_data;
};


}

#endif
