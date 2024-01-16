#ifndef MIXTUREPDF_H
#define MIXTUREPDF_H

#include "Pdf.h"
#include "Utils/RandomUtils.h"

namespace PathTracing
{

class MixturePdf : public Pdf {
  public:
    MixturePdf(Pdf* pdf1_param, Pdf* pdf2_param) {
        pdf1 = pdf1_param;
        pdf2 = pdf2_param;
    }

    double value(const glm::vec3& direction) const override {
        return 0.5 * pdf1->value(direction) + 0.5 *pdf2->value(direction);
    }

    glm::vec3 generate() const override {
        if (random_double() < 0.5)
            return pdf1->generate();
        else
            return pdf2->generate();
    }

  private:
    Pdf* pdf1;
    Pdf* pdf2;
};

}



#endif // MIXTUREPDF_H
