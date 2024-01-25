#include "MixturePdf.h"

#include "Utils/RandomUtils.h"

namespace PathTracing
{

double MixturePdf::value(const glm::vec3& direction) const
{
    double res = 0.0;
    for (const std::shared_ptr<Pdf>& pdf : m_listPdf)
    {
        res += pdf->value(direction);
    }
    return res/m_listPdf.size();
    //return 0.5 * pdf1->value(direction) + 0.5 *pdf2->value(direction);
}

glm::vec3 MixturePdf::generate(const Ray& rIn) const
{
    int random_index = Utils::randomInt(0, m_listPdf.size()-1);
    return m_listPdf[random_index]->generate(rIn);
    /*if (Utils::random_double() < 0.5)
        return pdf1->generate();
    else
        return pdf2->generate();*/
}

}
