#ifndef MIRRORPDF_H
#define MIRRORPDF_H

#include "Pdf.h"
#include <cmath>
namespace PathTracing
{
class MirrorPdf : public Pdf {
public:
    MirrorPdf(const glm::vec3& normal_param):m_normal(normal_param) {};

    double value(const glm::vec3& direction) const override {
        return 1;
    }

    glm::vec3 generate(Ray r_in) const override {
        //std::cout<<m_normal.y<<std::endl;
        float b = glm::dot(r_in.u(),m_normal);
        //float b = glm::dot(m_normal,r_in.u());
        glm::vec3 reflected_ray = r_in.u()+2.0f*b;
        return reflected_ray;
    }

private:
    glm::vec3 m_normal;

};
}


#endif // MIRRORPDF_H
