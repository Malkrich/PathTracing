#include "Plane.h"

#include <cmath>

namespace PathTracing
{

Plane::Plane(glm::vec3 const& position, glm::vec3 const& normal)
    : m_position(position)
    , m_normal(normal)
{}

bool Plane::intersect(Ray const& ray_param,IntersectData& intersection) const
{
    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs = ray_param.getP0();
    glm::vec3 const& u = ray_param.getU();
    glm::vec3 const& np = m_normal;
    glm::vec3 xp = m_position;

    float const t=-1.0f *glm::dot(xs-xp,np) / glm::dot(u,np);

    if(t>0)
    {
        glm::vec3 xInter = xs + t*u;
        intersection.set(xInter, np, t);
        return true;
    }
    else
        return false;
}

}
