#include "SceneObject.h"

namespace PathTracing
{

SceneObject::SceneObject(Primitive* primitive_param,Material* material_param):
    primitive(primitive_param),material(material_param)
{}

bool SceneObject::intersect(Ray const& ray_param,IntersectData& intersection) const
{
    bool IsIntersect = primitive->intersect(ray_param,intersection);
    if (IsIntersect)
    {
       intersection.setMaterial(material);
    }
    return IsIntersect;
};

}
