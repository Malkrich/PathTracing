#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Renderer/PathTracing/Ray.h"
#include "IntersectData.h"
#include "../Ray.h"
#include "../Materials/Material.h"

namespace PathTracing
{

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();

    //virtual bool intersect(Ray const& ray);
    virtual bool intersect(Ray const& ray_param,IntersectData& intersection) const = 0;



};

}

#endif // PRIMITIVE_H
