#include "Plane.h"

#include <cmath>

namespace PathTracing
{

Plane::Plane(glm::vec3 const& position, glm::vec3 const& normal)
    : m_position(position)
    , m_normal(normal)
{}

void Plane::rotate(const glm::quat& rotation)
{

}

bool Plane::intersect(Ray const& ray_param,IntersectData& intersection) const
{
    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs = ray_param.p0();
    glm::vec3 const& u = ray_param.u();
    glm::vec3 const& np = m_normal;
    glm::vec3 xp = m_position;

    float const t=-1.0f *dot(xs-xp,np)/dot(u,np);

    if(t>0)
    {
        glm::vec3 x_inter = xs+t*u;
        intersection.set(x_inter,np,t);
        return true;
    }
    else
        return false;
}

}
