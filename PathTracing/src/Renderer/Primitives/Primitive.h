#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Renderer/PathTracing/Ray.h"
#include "IntersectData.h"
#include "Renderer/PathTracing/Ray.h"
#include "Renderer/PathTracing/Materials/Material.h"

namespace PathTracing
{

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();

    //virtual bool intersect(Ray const& ray);
    virtual bool intersect(Ray const& ray_param,IntersectData& intersection) const = 0;
    virtual const glm::vec3& getPosition() const = 0;
    virtual glm::vec3& getPosition() = 0;
    virtual void rotate(const glm::quat& rotation) = 0;
};

}

#endif // PRIMITIVE_H
