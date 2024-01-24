#ifndef MIRRORPDF_H
#define MIRRORPDF_H

#include "Pdf.h"
#include <cmath>
namespace PathTracing
{

class MirrorPdf : public Pdf
{
public:
    MirrorPdf(const glm::vec3& normal)
        : m_normal(normal)
    {}

    virtual double value(const glm::vec3&) const override
    {
        return 1.0;
    }

    virtual glm::vec3 generate(const Ray& rIn) const override
    {
        //std::cout<<m_normal.y<<std::endl;
        float b = glm::dot(rIn.getU(), m_normal);
        //float b = glm::dot(m_normal,r_in.u());
        glm::vec3 reflected_ray = rIn.getU() + 2.0f*b;
        return reflected_ray;
    }

private:
    glm::vec3 m_normal;

};

}


#endif // MIRRORPDF_H
