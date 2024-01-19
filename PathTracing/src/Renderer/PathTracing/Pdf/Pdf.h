#ifndef PDF_H
#define PDF_H

#include <glm/glm.hpp>

namespace PathTracing
{

class Pdf {
public:
    virtual ~Pdf() {}

    virtual double value(const glm::vec3& direction) const = 0;
    virtual glm::vec3 generate() const = 0;
};

}
#endif // PDF_H
