#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <glm/glm.hpp>
#include <ostream>
#include "../Pdf/Pdf.h"

namespace PathTracing
{
struct IntersectData
{
    IntersectData();
    IntersectData(glm::vec3 const& position_param,
                      glm::vec3 const& normal_param,
                      float relative_param);

    /** Set all the fields of the intersection value */
    void set(glm::vec3 const& position_param,
             glm::vec3 const& normal_param,
             float relative_param);
    /** Set all the fields of the intersection value */
    void set(IntersectData const& intersection);


    /** 3D position of the intersection */
    glm::vec3 position;
    /** Normal of the shape at the intersection point */
    glm::vec3 normal;
    /** Relative position of the interesection along the ray
      * position = ray.p0 + relative*ray.u */
    float relative;

    Pdf* pdf;
};

std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection);
}

#endif // INTERSECTDATA_H
