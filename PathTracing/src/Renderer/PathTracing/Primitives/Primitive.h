#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Renderer/PathTracing/Ray.h"

namespace PathTracing
{

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();

    //virtual bool intersect(Ray const& ray);

};

}

#endif // PRIMITIVE_H
