#include "SceneData.h"

#define COPY_PTR(type)      std::make_shared<type>(static_cast<const type&>(*other))
#define CREATE_PTR(type)    std::make_shared<type>()

namespace PathTracing
{

//////////////////////////////////////////////////////
///////////////// PRIMITIVE //////////////////////////
//////////////////////////////////////////////////////
bool operator==(const CameraData& camera1, const CameraData& camera2)
{
    return camera1.position         == camera2.position
        && camera1.direction        == camera2.direction
        && camera1.screenDistance   == camera2.screenDistance;
}

std::shared_ptr<PrimitiveData> PrimitiveData::create(SceneObjectPrimitive primitive)
{
    switch(primitive)
    {
        case SceneObjectPrimitive::plane:       return CREATE_PTR(PlaneData);
        case SceneObjectPrimitive::rectangle:   return CREATE_PTR(RectangleData);
        case SceneObjectPrimitive::sphere:      return CREATE_PTR(SphereData);
        case SceneObjectPrimitive::box:         return CREATE_PTR(BoxData);
    }

    return nullptr;
}

std::shared_ptr<PrimitiveData> PrimitiveData::copy(const std::shared_ptr<PrimitiveData>& other)
{
    switch(other->getPrimitiveType())
    {
        case SceneObjectPrimitive::plane:       return COPY_PTR(PlaneData);
        case SceneObjectPrimitive::rectangle:   return COPY_PTR(RectangleData);
        case SceneObjectPrimitive::sphere:      return COPY_PTR(SphereData);
        case SceneObjectPrimitive::box:         return COPY_PTR(BoxData);
    }

    return nullptr;
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

bool BoxData::isEqual(const PrimitiveData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    auto box = static_cast<const BoxData&>(other);
    if(this->m_p2 != box.m_p2)
        return false;

    return PrimitiveData::isEqual(other);
}

bool operator==(const SceneObjectData& object1, const SceneObjectData& object2)
{
    return (object1.name        == object2.name)
        && (*object1.primitive  == *object2.primitive)
        && (*object1.material   == *object2.material);
}

bool operator==(const RenderSettings& settings1, const RenderSettings& settings2)
{
    return (settings1.samplePerPixel    == settings2.samplePerPixel)
        && (settings1.maxDepth          == settings2.maxDepth);
}

SceneData::SceneData()
    : m_sceneObjects()
    , m_renderSettings()
{}

//////////////////////////////////////////////////////
///////////////// MATERIAL ///////////////////////////
//////////////////////////////////////////////////////
std::shared_ptr<MaterialData> MaterialData::create(SceneObjectMaterial material)
{
    switch(material)
    {
        case SceneObjectMaterial::lambertian:   return CREATE_PTR(LambertianData);
        case SceneObjectMaterial::light:        return CREATE_PTR(LightData);
        case SceneObjectMaterial::mirror:       return CREATE_PTR(MirrorData);
    }

    return nullptr;
}

std::shared_ptr<MaterialData> MaterialData::copy(const std::shared_ptr<MaterialData>& other)
{
    switch(other->getMaterialType())
    {
        case SceneObjectMaterial::lambertian:   return COPY_PTR(LambertianData);
        case SceneObjectMaterial::light:        return COPY_PTR(LightData);
        case SceneObjectMaterial::mirror:       return COPY_PTR(MirrorData);
    }

    return nullptr;
}

bool MaterialData::operator==(const MaterialData& other) const
{
    return this->isEqual(other);
}

bool MaterialData::isEqual(const MaterialData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    return m_material   == other.m_material
        && m_color      == other.m_color;
}

bool LambertianData::isEqual(const MaterialData& other) const
{
    if(typeid(*this) != typeid(other))
        return false;

    return MaterialData::isEqual(other);
}

bool LightData::isEqual(const MaterialData& other) const
{
    if(typeid(*this) != typeid(other))
            return false;

    return MaterialData::isEqual(other);
}

bool MirrorData::isEqual(const MaterialData& other) const
{
    if(typeid(*this) != typeid(other))
            return false;

    return MaterialData::isEqual(other);
}

//////////////////////////////////////////////////////
//////////////// SCENE OBJECT ////////////////////////
//////////////////////////////////////////////////////
void SceneData::addObject(const SceneObjectData& object)
{
    m_sceneObjects.push_back(object);
}

void SceneData::addObject(const std::string& name,
                          std::shared_ptr<PrimitiveData> primitive,
                          std::shared_ptr<MaterialData> material)
{
    SceneObjectData sceneObject(name, primitive, material);
    addObject(sceneObject);
}

void SceneData::addPlane(const std::string& name,
                         const glm::vec3& position, const glm::vec3& normal,
                         std::shared_ptr<MaterialData> material)
{
    std::shared_ptr<PlaneData> plane = std::make_shared<PlaneData>(position, normal);
    addObject(name, plane, material);
}

void SceneData::addRectangle(const std::string& name,
                             const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2,
                             std::shared_ptr<MaterialData> material)
{
    std::shared_ptr<RectangleData> rectangle = std::make_shared<RectangleData>(position, v1, v2);
    addObject(name, rectangle, material);
}

void SceneData::addSphere(const std::string& name,
                          const glm::vec3& position, float radius,
                          std::shared_ptr<MaterialData> material)
{
    std::shared_ptr<SphereData> sphere = std::make_shared<SphereData>(position, radius);
    addObject(name, sphere, material);
}


void SceneData::addBox(const std::string& name,
                          const glm::vec3& p1, const glm::vec3& p2,
                          std::shared_ptr<MaterialData> material)
{
    std::shared_ptr<BoxData> box = std::make_shared<BoxData>(p1, p2);
    addObject(name, box, material);
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
