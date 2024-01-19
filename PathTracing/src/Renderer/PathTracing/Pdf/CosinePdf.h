#ifndef COSINEPDF_H
#define COSINEPDF_H

#include "Pdf.h"
#include "OrthonormalBasis.h"
#include <cmath>
#include "../../../Utils/RandomUtils.h"

namespace PathTracing
{

class CosinePdf : public Pdf {
public:
    CosinePdf(const glm::vec3& w) { uvw.build_from_w(w); }

    double value(const glm::vec3& direction) const override {
        auto cosine_theta = dot(glm::normalize(direction), uvw.w());
        return fmax(0, cosine_theta/M_PI);
    }

    glm::vec3 generate() const override {
        auto r1 = Utils::random_double();
        auto r2 = Utils::random_double();

        auto phi = 2*M_PI*r1;
        auto x = cos(phi)*sqrt(r2);
        auto y = sin(phi)*sqrt(r2);
        auto z = sqrt(1-r2);

        glm::vec3 v{x,y,z};
        return uvw.local(v);
    }

private:
    OrthonormalBasis uvw;
};

}



#endif // COSINEPDF_H
