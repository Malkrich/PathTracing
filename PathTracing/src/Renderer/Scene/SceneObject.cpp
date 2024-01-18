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

double SceneObject::pdf_value(const glm::vec3 &o,const glm::vec3 &n, const glm::vec3 &v) const
{
    return primitive->pdf_value(o,n,v);
}

glm::vec3 SceneObject::random(const glm::vec3 &o) const
{
    //std::cout<<"Name SceneObject"<<name<<std::endl;
    return primitive->random(o);
}

}
