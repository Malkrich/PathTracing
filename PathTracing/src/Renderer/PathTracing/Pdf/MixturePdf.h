#ifndef MIXTUREPDF_H
#define MIXTUREPDF_H

#include <memory>
#include <vector>
#include <iostream>

#include "Pdf.h"

namespace PathTracing
{

class MixturePdf : public Pdf
{
public:
    MixturePdf(const std::vector<std::shared_ptr<Pdf>>& listPdf)
        : m_listPdf(listPdf)
    {}

    virtual double value(const glm::vec3& direction) const override;
    virtual glm::vec3 generate(const Ray& rIn) const override;

private:
    //std::shared_ptr<Pdf> pdf1;
    //std::shared_ptr<Pdf> pdf2;
    std::vector<std::shared_ptr<Pdf>> m_listPdf;

};

}



#endif // MIXTUREPDF_H
