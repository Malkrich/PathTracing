#include "Scene.h"

namespace PathTracing
{
Scene::Scene()
{
    list_object = std::vector<SceneObject>();
}

void Scene::push_back(SceneObject object)
{
    list_object.push_back(object);
}

}
