#include "SceneRenderingController.h"

#include <thread>
#include <functional>

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

static std::shared_ptr<SceneObject> createSceneObject(const SceneObjectData& sceneObject)
{
    std::shared_ptr<Primitive> primitive = sceneObject.primitive->createPrimitive();
    std::shared_ptr<Material> material = sceneObject.material->createMaterial();

    return std::make_shared<SceneObject>(primitive, material, sceneObject.name);
}

static Camera createCamera(const CameraData& cameraData, unsigned int width, unsigned int height)
{
    const glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 direction = glm::vec3(cameraData.direction, 1.0);
    return Camera(cameraData.position, direction, upVector, cameraData.screenDistance, width, height);
}

}

SceneRenderingController::SceneRenderingController()
    : m_width(0)
    , m_height(0)
{
    m_sceneData.reset(new SceneData());
    m_image.reset(new Image(m_width, m_height));
}

void SceneRenderingController::setSceneData(std::shared_ptr<SceneData> sceneData)
{
    if(*m_sceneData == *sceneData) // we check if all of the scene data are similar
    {
        m_sceneHasNewData = false;
        return;
    }
    else
    {
        m_sceneHasNewData = true;
        m_sceneData = std::make_shared<SceneData>(*sceneData);
        updateSceneFromSceneData();
    }
}

void SceneRenderingController::updateSceneFromSceneData()
{
    Camera camera = Utils::createCamera(m_sceneData->getCameraData(), m_width, m_height);
    m_scene.reset(new Scene(camera));

    for(const auto& objectData : *m_sceneData)
    {
        std::shared_ptr<SceneObject> sceneObject = Utils::createSceneObject(objectData);
        m_scene->addObject(sceneObject);
    }
    m_scene->setRenderSettings(m_sceneData->getRenderSettings());
}


void SceneRenderingController::renderThread()
{
    m_isRendering = true;

    PathTracer::pathTrace(m_image, m_scene);

    m_isRendering = false;
}

void SceneRenderingController::startRenderingThread()
{
    if(m_width != m_image->getWidth() || m_height != m_image->getHeight())
    {
        m_scene->getCamera().resize(m_width, m_height);
        m_image->resize(m_width, m_height);
        m_image->clearData();
        PathTracer::resetAccumultationCount();
    }

    if(m_sceneHasNewData)
    {
        m_image->clearData();
        PathTracer::resetAccumultationCount();
    }

    std::thread t(std::bind(&SceneRenderingController::renderThread, std::placeholders::_1), this);
    t.detach();
}

void SceneRenderingController::resizeImage(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
}

}
