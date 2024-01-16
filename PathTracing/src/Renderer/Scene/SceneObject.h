#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Renderer/Primitives/Primitive.h"
#include "Renderer/PathTracing/Materials/Material.h"

namespace PathTracing
{

    struct SceneObject
    {
        SceneObject(std::shared_ptr<Primitive> primitive_param, std::shared_ptr<Material> material_param, const std::string& name_param);

        bool intersect(Ray const& ray_param, IntersectData& intersection) const;

        const std::string& getName() const { return name; }

        std::shared_ptr<Primitive> primitive;
        std::shared_ptr<Material> material;
        std::string name;
    };

}

#endif // SCENEOBJECT_H
