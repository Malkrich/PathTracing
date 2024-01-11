#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../Primitives/Primitive.h"
#include "../Materials/Material.h"

namespace PathTracing
{

    struct SceneObject
    {
        SceneObject(Primitive* primitive_param,Material* material_param);

        Primitive* primitive;
        Material* material;
    };

}

#endif // SCENEOBJECT_H
