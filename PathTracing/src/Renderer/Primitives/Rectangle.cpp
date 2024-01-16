#include "Rectangle.h"

#include <cmath>

namespace PathTracing
{

Rectangle::Rectangle(const glm::vec3& p, const glm::vec3& v1, const glm::vec3& v2)
    : m_p(p)
    , m_v1(v1)
    , m_v2(v2)
{
    m_normal = glm::normalize(glm::cross(v1, v2));
}

void Rectangle::rotate(const glm::quat& rotation)
{

}

bool Rectangle::intersect(const Ray& ray_param, IntersectData& intersection) const
{

    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs        = ray_param.p0();
    const glm::vec3& u  = ray_param.u();
    const glm::vec3& np = m_normal;
    glm::vec3 xp        = m_p;

    const float t = -1.0f * glm::dot(xs-xp,np) / glm::dot(u,np);

    if(t > 0)
    {
        glm::vec3 x_inter   = xs+t*u;
        glm::vec3 w         = np / glm::dot(np,cross(m_v1, m_v2));
        glm::vec3 p         = x_inter-xp;
        float alpha         = glm::dot(w,cross(p, m_v2)) ; //MAybe To change
        float beta          = glm::dot(w,cross(m_v1, p)); //MAybe To change

        if (0 < alpha && alpha < 1 && 0 < beta && beta < 1)
        {
            intersection.set(x_inter, np, t);
            return true;
        }
    }

    return false;


}

}
