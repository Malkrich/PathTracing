#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Renderer/PathTracing/Ray.h"
#include "../Materials/Material.h"

namespace PathTracing
{

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();

    //virtual bool intersect(Ray const& ray);

private:
    Material* material;

};

}

#endif // PRIMITIVE_H
