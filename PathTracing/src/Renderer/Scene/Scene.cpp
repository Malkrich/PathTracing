#include "Scene.h"

namespace PathTracing
{
Scene::Scene()
    : m_objectList()
    , m_camera()
{}

Scene::Scene(const Camera& camera)
    : m_objectList()
    , m_camera(camera)
{}

void Scene::addObject(SceneObject* object)
{
    m_objectList.push_back(object);
}

}
