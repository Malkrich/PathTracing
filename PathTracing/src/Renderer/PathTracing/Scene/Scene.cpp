#include "Scene.h"

namespace PathTracing
{
Scene::Scene()
{
    list_object = std::vector<SceneObject*>();
    cam = Camera();
}

Scene::Scene(Camera cam_param)
{
    list_object = std::vector<SceneObject*>();
    cam = cam_param;
}

void Scene::push_back(SceneObject* object)
{
    list_object.push_back(object);
}

Camera const& Scene::getCamera() const
{
    return cam;
}

std::vector<SceneObject*> const& Scene::getListObject() const
{
    return list_object;
}

int const Scene::size_primitive() const
{
    return list_object.size();
}

SceneObject* Scene::getSceneObject(int index) const
{
    return list_object[index];
}

Primitive const& Scene::get_primitive(int index) const
{
    return *( list_object[index]->primitive );
}

Material const& Scene::get_material(int index) const
{
    return * (list_object[index]->material);
}

}
