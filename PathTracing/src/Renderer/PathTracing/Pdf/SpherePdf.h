#ifndef SPHEREPDF_H
#define SPHEREPDF_H

#include <cmath>
#include <glm/glm.hpp>
#include "Pdf.h"

namespace PathTracing
{
class SpherePdf : public Pdf {
  public:
    SpherePdf() { }

    double value(const glm::vec3& direction) const override {
        return 1/ (4 * M_PI);
    }

    /*glm::vec3 generate() const override {
        return random_unit_vector();
    }*/
};
}



#endif // SPHEREPDF_H
