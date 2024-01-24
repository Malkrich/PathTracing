#ifndef Ray_HPP
#define Ray_HPP

#include <glm/glm.hpp>
#include <iostream>

namespace PathTracing
{

/** Ray (initial position + direction) used for Ray-tracing algorithm (can be seen as a half line) */
class Ray
{
public:
    Ray();
    Ray(const glm::vec3& p0, const glm::vec3& u);
    Ray(const glm::vec3& p0, const glm::vec3& u,int depth);

    /** Starting point */
    const glm::vec3& getP0() const { return m_p0; }
    /** Direction */
    const glm::vec3& getU() const { return m_u; }

    unsigned int getDepth() const { return m_depth; }

    /** Evaluate 3D position at x0+t*u */
    glm::vec3 operator()(float t) const;
    /** Offset the Ray by epsilon in the direction of the Ray */
    void addOffset(float const epsilon = 1e-3f);

    glm::vec3 getValue();

private:
    /** Internal initial position of the Ray */
    glm::vec3 m_p0;
    /** Internal direction of the Ray */
    glm::vec3 m_u;

    unsigned int m_depth;
};

/** Exporting Ray data */
//std::ostream& operator<<(std::ostream& stream,Ray const& r);

}



#endif

