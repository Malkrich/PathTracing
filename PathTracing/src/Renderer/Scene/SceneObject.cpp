#include "SceneObject.h"

namespace PathTracing
{

SceneObject::SceneObject(Primitive* primitive_param,Material* material_param, const std::string& name_param)
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

double SceneObject::pdf_value(const glm::vec3 &o, const glm::vec3 &v) const
{
    return primitive->pdf_value(o,v);
}

glm::vec3 SceneObject::random(const glm::vec3 &o) const
{
    return primitive->random(o);
}

}
