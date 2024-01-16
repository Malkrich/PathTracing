#include "SceneObject.h"

namespace PathTracing
{

SceneObject::SceneObject(std::shared_ptr<Primitive> primitive_param, std::shared_ptr<Material> material_param, const std::string& name_param)
    : primitive(primitive_param)
    , material(material_param)
    , name(name_param)
{}

bool SceneObject::intersect(Ray const& ray_param, IntersectData& intersection) const
{
    bool IsIntersect = primitive->intersect(ray_param, intersection);
    if (IsIntersect)
    {
       intersection.setMaterial(material);
    }
    return IsIntersect;
};

}
