#ifndef MIXTUREPDF_H
#define MIXTUREPDF_H

#include <memory>

#include "Pdf.h"
#include "Utils/RandomUtils.h"

namespace PathTracing
{

class MixturePdf : public Pdf {
  public:
    MixturePdf(std::shared_ptr<Pdf> pdf1_param, std::shared_ptr<Pdf> pdf2_param) {
        pdf1 = pdf1_param;
        pdf2 = pdf2_param;
    }

    double value(const glm::vec3& direction) const override {
        return 0.5 * pdf1->value(direction) + 0.5 *pdf2->value(direction);
    }

    glm::vec3 generate() const override {
        if (Utils::random_double() < 0.5)
            return pdf1->generate();
        else
            return pdf2->generate();
    }

  private:
    std::shared_ptr<Pdf> pdf1;
    std::shared_ptr<Pdf> pdf2;
};

}



#endif // MIXTUREPDF_H
