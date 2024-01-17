#include "SceneData.h"

namespace PathTracing
{

SceneData::SceneData()
    : m_sceneObjects()
    , m_renderSettings()
{}

void SceneData::addObject(const SceneObjectData& object)
{
    m_sceneObjects.push_back(object);
}

void SceneData::addObject(const std::string& name,
                          std::shared_ptr<PrimitiveData> primitive,
                          SceneObjectMaterial material, const glm::vec3& color)
{
    SceneObjectData sceneObject(name, primitive, material, color);
    addObject(sceneObject);
}

void SceneData::addPlane(const std::string& name,
                         const glm::vec3& position, const glm::vec3& normal,
                         SceneObjectMaterial material, const glm::vec3& color)
{
    std::shared_ptr<PlaneData> plane = std::make_shared<PlaneData>(position, normal);
    addObject(name, plane, material, color);
}

void SceneData::addRectangle(const std::string& name,
                             const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2,
                             SceneObjectMaterial material, const glm::vec3& color)
{
    std::shared_ptr<RectangleData> rectangle = std::make_shared<RectangleData>(position, v1, v2);
    addObject(name, rectangle, material, color);
}

void SceneData::addSphere(const std::string& name,
                          const glm::vec3& position, float radius,
                          SceneObjectMaterial material, const glm::vec3& color)
{
    std::shared_ptr<SphereData> sphere = std::make_shared<SphereData>(position, radius);
    addObject(name, sphere, material, color);
}

}
