#ifndef HITTABLEPDF_H
#define HITTABLEPDF_H

#include "Pdf.h"
#include "glm/glm.hpp"
#include "Renderer/Scene/SceneObject.h"

namespace PathTracing
{

class HittablePdf : public Pdf {
  public:
    HittablePdf(const SceneObject& obj, const glm::vec3& origin)
      : objects(obj), origin(origin)
    {}

    double value(const glm::vec3& direction) const override {
        return objects.pdf_value(origin, direction);
    }

    glm::vec3 generate() const override {
        return objects.random(origin);
    }

  private:
    const SceneObject& objects;
    glm::vec3 origin;
};


}

#endif // HITTABLEPDF_H
