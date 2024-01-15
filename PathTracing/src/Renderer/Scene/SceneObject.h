#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Renderer/Primitives/Primitive.h"
#include "Renderer/PathTracing/Materials/Material.h"

namespace PathTracing
{

    struct SceneObject
    {
        SceneObject(Primitive* primitive_param,Material* material_param);
        bool intersect(Ray const& ray_param,IntersectData& intersection) const;

        Primitive* primitive;
        Material* material;
    };

}

#endif // SCENEOBJECT_H
