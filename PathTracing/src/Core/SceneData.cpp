#include "SceneData.h"

namespace PathTracing
{

bool operator==(const CameraData& camera1, const CameraData& camera2)
{
    return camera1.position         == camera2.position
        && camera1.direction        == camera2.direction
        && camera1.screenDistance   == camera2.screenDistance;
}

bool PrimitiveData::operator==(const PrimitiveData& other)
{
    return this->isEqual(other);
}

bool PrimitiveData::isEqual(const PrimitiveData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    return m_primitive == other.m_primitive
        && m_position == other.m_position;
}


bool PlaneData::isEqual(const PrimitiveData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    auto plane = static_cast<const PlaneData&>(other);
    if(this->m_normal != plane.m_normal)
        return false;

    return PrimitiveData::isEqual(other);
}


bool RectangleData::isEqual(const PrimitiveData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    auto rectangle = static_cast<const RectangleData&>(other);
    if(this->m_v1 != rectangle.m_v1 || this->m_v2 != rectangle.m_v2)
        return false;

    return PrimitiveData::isEqual(other);
}

bool SphereData::isEqual(const PrimitiveData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    auto sphere = static_cast<const SphereData&>(other);
    if(this->m_radius != sphere.m_radius)
        return false;

    return PrimitiveData::isEqual(other);
}

bool operator==(const SceneObjectData& object1, const SceneObjectData& object2)
{
    return (object1.name == object2.name)
        && (*object1.primitive == *object2.primitive)
        && (object1.material == object2.material)
        && (object1.color == object2.color);
}

bool operator==(const RenderSettings& settings1, const RenderSettings& settings2)
{
    return (settings1.samplePerPixel == settings2.samplePerPixel)
        && (settings1.maxDepth == settings2.maxDepth);
}

SceneData::SceneData()
    : m_sceneObjects()
    , m_renderSettings()
{}

static std::shared_ptr<PrimitiveData> createPrimitive(const std::shared_ptr<PrimitiveData>& primitive)
{
    switch(primitive->getPrimitiveType())
    {
        case SceneObjectPrimitive::plane:       return std::make_shared<PlaneData>(static_cast<const PlaneData&>(*primitive));
        case SceneObjectPrimitive::rectangle:   return std::make_shared<RectangleData>(static_cast<const RectangleData&>(*primitive));
        case SceneObjectPrimitive::sphere:      return std::make_shared<SphereData>(static_cast<const SphereData&>(*primitive));
    }
}

SceneObjectData::SceneObjectData(const SceneObjectData& other)
    : name(other.name)
    , material(other.material)
    , color(other.color)
{
    primitive = createPrimitive(other.primitive);
}

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

bool operator==(const SceneData& scene1, const SceneData& scene2)
{
    if(scene1.getSceneObjectsCount() != scene2.getSceneObjectsCount())
        return false;

    bool sameRenderSettings = scene1.getRenderSettings() == scene2.getRenderSettings();
    bool sameCamera = scene1.getCameraData() == scene2.getCameraData();
    // scene objects has the same size
    bool sameSceneObject = true;

    for(unsigned int i = 0; i < scene1.getSceneObjectsCount(); i++)
        sameSceneObject &= scene1.getSceneObject(i) == scene2.getSceneObject(i);

    return sameRenderSettings && sameCamera && sameSceneObject;
}

}
