#ifndef HITTABLEPDF_H
#define HITTABLEPDF_H

#include "Pdf.h"
#include "glm/glm.hpp"
#include "Renderer/Scene/SceneObject.h"

namespace PathTracing
{

class HittablePdf : public Pdf {
  public:
    HittablePdf(const SceneObject& obj, const glm::vec3& origin, const glm::vec3& normal_param)
      : objects(obj), origin(origin),normal(normal_param)
    {}

    double value(const glm::vec3& direction) const override {
        return objects.pdf_value(origin,normal, direction);
    }

    glm::vec3 generate(Ray r_in) const override {
        return objects.random(origin);
    }

  private:
    const SceneObject& objects; //Objet que l'on vise, par exemple la lumiere
    glm::vec3 origin; //Point de l'intersection (pas la lumiere)
    glm::vec3 normal; //Normal de l'intersection (pas la lumiere)
};


}

#endif // HITTABLEPDF_H
