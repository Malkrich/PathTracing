#ifndef MIXTUREPDF_H
#define MIXTUREPDF_H

#include <memory>
#include <vector>
#include <iostream>

#include "Pdf.h"
#include "Utils/RandomUtils.h"

namespace PathTracing
{

class MixturePdf : public Pdf
{
public:
    MixturePdf(const std::vector<std::shared_ptr<Pdf>>& listPdf)
        : m_listPdf(listPdf)
    {}

    virtual double value(const glm::vec3& direction) const override
    {
        double res = 0.0;
        for (const std::shared_ptr<Pdf>& pdf : m_listPdf)
        {
            res += pdf->value(direction);
        }
        return res/m_listPdf.size();
        //return 0.5 * pdf1->value(direction) + 0.5 *pdf2->value(direction);
    }

    virtual glm::vec3 generate(const Ray& r_in) const override
    {
        int random_index = Utils::random_int(0,m_listPdf.size()-1);
        return m_listPdf[random_index]->generate(r_in);
        /*if (Utils::random_double() < 0.5)
            return pdf1->generate();
        else
            return pdf2->generate();*/
    }

private:
    //std::shared_ptr<Pdf> pdf1;
    //std::shared_ptr<Pdf> pdf2;
    std::vector<std::shared_ptr<Pdf>> m_listPdf;

};

}



#endif // MIXTUREPDF_H
