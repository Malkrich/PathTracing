#include "Scene.h"

namespace PathTracing
{

Scene::Scene(const Camera& camera)
    : m_objectList()
    , m_camera(camera)
{}

void Scene::addObject(std::shared_ptr<SceneObject> object)
{
    m_objectList.push_back(object);
    if (object->material->CanEmit())
    {
        int indexNewObject = m_objectList.size()-1;
        m_listIndexLight.push_back(indexNewObject);
    }
}

const std::vector<std::shared_ptr<SceneObject>> Scene::getLights() const
{
   std::vector<std::shared_ptr<SceneObject>> listLights;
   for (int index : m_listIndexLight)
   {
       std::shared_ptr<SceneObject> light = getSceneObject(index);
       listLights.push_back(light);
   }
   return listLights;
}

}
