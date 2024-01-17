#include "SceneRenderingController.h"

#include <thread>

#include "Renderer/PathTracing/PathTracer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Renderer/Primitives/Primitive.h"
#include "Renderer/PathTracing/Materials/Lambertian.h"
#include "Renderer/PathTracing/Materials/Light.h"
#include "Renderer/PathTracing/PathTracer.h"

namespace PathTracing
{

namespace Utils
{

std::shared_ptr<Material> createMaterial(const SceneObjectData& sceneObject)
{
    switch(sceneObject.material)
    {
        case SceneObjectMaterial::lambertien:   return std::make_shared<Lambertian>(sceneObject.color);
        case SceneObjectMaterial::light:        return std::make_shared<Light>(sceneObject.color);
    }
}

std::shared_ptr<SceneObject> createSceneObject(const SceneObjectData& sceneObject)
{
    std::shared_ptr<Primitive> primitive = sceneObject.primitive->createPrimitive();
    std::shared_ptr<Material> material = createMaterial(sceneObject);

    return std::make_shared<SceneObject>(primitive, material, sceneObject.name);
}

}

static void renderThread(std::shared_ptr<Image> image, std::shared_ptr<Scene> m_scene, bool* isRendering)
{
    *isRendering = true;

    PathTracer::pathTrace(image, m_scene);

    *isRendering = false;
}

SceneRenderingController::SceneRenderingController()
{
    m_sceneData.reset(new SceneData());
    m_image.reset(new Image(Renderer::getViewportWidth(), Renderer::getViewportHeight()));
}

void SceneRenderingController::updateSceneFromSceneData()
{
    // TODO : move camera construction to editor.
    Camera camera(Renderer::getViewportWidth(), Renderer::getViewportHeight());
    m_scene.reset(new Scene(camera));

    for(const auto& objectData : *m_sceneData)
    {
        std::shared_ptr<SceneObject> sceneObject = Utils::createSceneObject(objectData);
        m_scene->addObject(sceneObject);
    }
    m_scene->setRenderSettings(m_sceneData->getRenderSettings());
}

void SceneRenderingController::startRenderingThread()
{
    std::thread t(renderThread, m_image, m_scene, &m_isRendering);
    t.detach();
}

}
