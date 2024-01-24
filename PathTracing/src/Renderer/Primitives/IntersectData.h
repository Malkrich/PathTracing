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
public:
    IntersectData();
    IntersectData(const glm::vec3& position,
                  const glm::vec3& normal,
                  float relative_param,
                  std::shared_ptr<Pdf> pdf,
                  std::shared_ptr<Material> material);

    /** Set all the fields of the intersection value */
    void set(glm::vec3 const& position,
             glm::vec3 const& normal,
             float relative);
    /** Set all the fields of the intersection value */
    //void set(IntersectData const& intersection);

    void setPdf(std::shared_ptr<Pdf> pdf);
    void setMaterial(std::shared_ptr<Material> material);

    Ray create_ray(Ray r_in,int depth);
    //float getValue(Ray outray, Ray inray);
    glm::vec3 getValue(const Ray& rayOut, const Ray& rayIn);

public:
    /** 3D position of the intersection */
    glm::vec3 m_position;
    /** Normal of the shape at the intersection point */
    glm::vec3 m_normal;
    /** Relative position of the interesection along the ray
      * position = ray.p0 + relative*ray.u */
    float m_relative;
    /*Probability density function*/
    std::shared_ptr<Pdf> m_pdf;
    std::shared_ptr<Material> m_material;
};


}

#endif // INTERSECTDATA_H
