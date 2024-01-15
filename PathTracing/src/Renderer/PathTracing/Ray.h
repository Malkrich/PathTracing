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
    Ray(glm::vec3 const& p0_param,glm::vec3 const& u_param);
    Ray(glm::vec3 const& p0_param,glm::vec3 const& u_param,int const depth_param);

    /** Starting point */
    glm::vec3 const& p0() const;
    /** Direction */
    glm::vec3 const& u() const;

    int const depth() const;


    /** Evaluate 3D position at x0+t*u */
    glm::vec3 operator()(float t) const;
    /** Offset the Ray by epsilon in the direction of the Ray */
    void offset(float const epsilon = 1e-3f);

    glm::vec3 getValue();


private:
    /** Internal initial position of the Ray */
    glm::vec3 p0_data;
    /** Internal direction of the Ray */
    glm::vec3 u_data;

    int depth_data;
};


/** Exporting Ray data */
std::ostream& operator<<(std::ostream& stream,Ray const& r);



}



#endif

