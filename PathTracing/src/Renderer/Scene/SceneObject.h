#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Renderer/Primitives/Primitive.h"
#include "Renderer/PathTracing/Materials/Material.h"

namespace PathTracing
{

    struct SceneObject
    {
        SceneObject(Primitive* primitive_param, Material* material_param, const std::string& name_param);

        bool intersect(Ray const& ray_param, IntersectData& intersection) const;

        const std::string& getName() const { return name; }

        double pdf_value(const glm::vec3& o, const glm::vec3& v) const;

        glm::vec3 random(const glm::vec3& o) const;

        Primitive* primitive;
        Material* material;
        std::string name;
    };

}

#endif // SCENEOBJECT_H
