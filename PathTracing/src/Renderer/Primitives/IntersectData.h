#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <memory>

#include <glm/glm.hpp>
#include <ostream>
#include "Renderer/PathTracing/Pdf/Pdf.h"
#include "Renderer/PathTracing/Ray.h"
#include "Renderer/PathTracing/Materials/Material.h"

namespace PathTracing
{

struct IntersectData
{
    IntersectData();
    IntersectData(const glm::vec3& position_param,
                  const glm::vec3& normal_param,
                  float relative_param,
                  std::shared_ptr<Pdf> pdf,
                  std::shared_ptr<Material> material);

    /** Set all the fields of the intersection value */
    void set(glm::vec3 const& position_param,
             glm::vec3 const& normal_param,
             float relative_param);
    /** Set all the fields of the intersection value */
    //void set(IntersectData const& intersection);

    void setPdf(std::shared_ptr<Pdf> pdf);
    void setMaterial(std::shared_ptr<Material> material);

    Ray create_ray(int depth);
    //float getValue(Ray outray, Ray inray);
    glm::vec3 getValue(Ray outray, Ray inray);


    /** 3D position of the intersection */
    glm::vec3 position;
    /** Normal of the shape at the intersection point */
    glm::vec3 normal;
    /** Relative position of the interesection along the ray
      * position = ray.p0 + relative*ray.u */
    float relative;
    /*Probability density function*/
    std::shared_ptr<Pdf> pdf;
    std::shared_ptr<Material> material;
};

//std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection);

}

#endif // INTERSECTDATA_H
