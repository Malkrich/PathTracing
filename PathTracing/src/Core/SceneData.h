#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Renderer/Primitives/Primitive.h"
#include "Renderer/Primitives/Rectangle.h"
#include "Renderer/Primitives/Plane.h"
#include "Renderer/Primitives/Sphere.h"
#include "Renderer/PathTracing/Materials/Material.h"
#include "Renderer/PathTracing/Materials/Lambertian.h"
#include "Renderer/PathTracing/Materials/Light.h"

namespace PathTracing
{
//////////////////////////////////////////////////////
////////////////// CAMERA ////////////////////////////
//////////////////////////////////////////////////////
struct CameraData
{
    CameraData()
        : position(glm::vec3(0.0f, 0.0f, -2.0f))
        , direction(glm::vec2(0.0f, 0.0f))
        , screenDistance(2.0f)
    {}

    glm::vec3 position;
    glm::vec2 direction;
    float screenDistance;
};

bool operator==(const CameraData& camera1, const CameraData& camera2);

//////////////////////////////////////////////////////
///////////////// PRIMITIVE //////////////////////////
//////////////////////////////////////////////////////
enum class SceneObjectPrimitive
{
    plane = 0,
    rectangle,
    sphere
};

class PrimitiveData
{
public:
    PrimitiveData(SceneObjectPrimitive primitive, const glm::vec3& position)
        : m_primitive(primitive)
        , m_position(position)
    {}

    static std::shared_ptr<PrimitiveData> create(SceneObjectPrimitive primitive);
    static std::shared_ptr<PrimitiveData> copy(const std::shared_ptr<PrimitiveData>& other);

    const glm::vec3& getPosition() const { return m_position; }

    SceneObjectPrimitive getPrimitiveType() const { return m_primitive; }

    virtual std::shared_ptr<Primitive> createPrimitive() const = 0;

    bool operator==(const PrimitiveData& other);

protected:
    virtual bool isEqual(const PrimitiveData& other) const;

protected:
    SceneObjectPrimitive m_primitive;
    glm::vec3 m_position;
};

class PlaneData : public PrimitiveData
{
public:
    PlaneData()
        : PlaneData({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f})
    {}

    PlaneData(const glm::vec3& position, const glm::vec3& normal)
        : PrimitiveData(SceneObjectPrimitive::plane, position)
        , m_normal(normal)
    {}

    const glm::vec3& getNormal() const { return m_normal; }

    virtual std::shared_ptr<Primitive> createPrimitive() const override
    {
        return std::make_shared<Plane>(m_position, m_normal);
    }

protected:
    virtual bool isEqual(const PrimitiveData& other) const override;

private:
    glm::vec3 m_normal;
};

class RectangleData : public PrimitiveData
{
public:
    RectangleData()
        : RectangleData({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f})
    {}

    RectangleData(const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2)
        : PrimitiveData(SceneObjectPrimitive::rectangle, position)
        , m_v1(v1)
        , m_v2(v2)
    {}

    const glm::vec3& getV1() const { return m_v1; }
    const glm::vec3& getV2() const { return m_v2; }

    virtual std::shared_ptr<Primitive> createPrimitive() const override
    {
        return std::make_shared<Rectangle>(m_position, m_v1, m_v2);
    }

protected:
    virtual bool isEqual(const PrimitiveData& other) const override;

private:
    glm::vec3 m_v1;
    glm::vec3 m_v2;
};

class SphereData : public PrimitiveData
{
public:
    SphereData()
        : SphereData({0.0f, 0.0f, 0.0f}, 1.0f)
    {}

    SphereData(const glm::vec3& position, float radius)
        : PrimitiveData(SceneObjectPrimitive::sphere, position)
        , m_radius(radius)
    {}

    const float& getRadius() const { return m_radius; }

    virtual std::shared_ptr<Primitive> createPrimitive() const override
    {
        return std::make_shared<Sphere>(m_position, m_radius);
    }

protected:
    virtual bool isEqual(const PrimitiveData& other) const override;

private:
    float m_radius;
};

//////////////////////////////////////////////////////
///////////////// MATERIAL ///////////////////////////
//////////////////////////////////////////////////////
enum class SceneObjectMaterial
{
    lambertian = 0,
    light,
    mirror
};

class MaterialData
{
public:
    MaterialData(SceneObjectMaterial material, const glm::vec3& color)
        : m_material(material)
        , m_color(color)
    {}

    static std::shared_ptr<MaterialData> create(SceneObjectMaterial material);
    static std::shared_ptr<MaterialData> copy(const std::shared_ptr<MaterialData>& other);

    SceneObjectMaterial getMaterialType() const { return m_material; }
    const glm::vec3& getColor() const { return m_color; }

    virtual std::shared_ptr<Material> createMaterial() const = 0;

    bool operator==(const MaterialData& other) const;

protected:
    virtual bool isEqual(const MaterialData& other) const;

protected:
    SceneObjectMaterial m_material;
    glm::vec3 m_color;
};

class LambertianData : public MaterialData
{
public:
    LambertianData()
        : MaterialData(SceneObjectMaterial::lambertian, glm::vec3(0.2f, 0.2f, 0.2f))
    {}

    LambertianData(const glm::vec3& color)
        : MaterialData(SceneObjectMaterial::lambertian, color)
    {}

    virtual std::shared_ptr<Material> createMaterial() const override
    {
        return std::make_shared<Lambertian>(m_color);
    }

protected:
    virtual bool isEqual(const MaterialData& other) const override;
};

class LightData : public MaterialData
{
public:
    LightData()
        : MaterialData(SceneObjectMaterial::light, glm::vec3(1.0f, 1.0f, 1.0f))
    {}

    LightData(const glm::vec3& color)
        : MaterialData(SceneObjectMaterial::light, color)
    {}

    virtual std::shared_ptr<Material> createMaterial() const override
    {
        return std::make_shared<Light>(m_color);
    }

protected:
    virtual bool isEqual(const MaterialData& other) const override;
};


//////////////////////////////////////////////////////
//////////////// SCENE OBJECT ////////////////////////
//////////////////////////////////////////////////////
struct SceneObjectData
{
    SceneObjectData(const std::string& name)
        : SceneObjectData(name,
                          std::make_shared<RectangleData>(glm::vec3(0.0f, 0.0f, 0.0f),
                                                          glm::vec3(0.0f, 1.0f, 0.0f),
                                                          glm::vec3(1.0f, 0.0f, 0.0f)),
                          std::make_shared<LambertianData>(glm::vec3(0.2f, 0.2f, 0.2f)))
    {}

    SceneObjectData(const std::string& name,
                    std::shared_ptr<PrimitiveData> primitive,
                    std::shared_ptr<MaterialData> material)
        : name(name)
        , primitive(primitive)
        , material(material)
    {}

    SceneObjectData(const SceneObjectData& other)
        : name(other.name)
    {
        primitive   = PrimitiveData::copy(other.primitive);
        material    = MaterialData::copy(other.material);
    }

    // global data
    std::string name;

    // geometry data
    std::shared_ptr<PrimitiveData> primitive;

    // material data
    std::shared_ptr<MaterialData> material;
};

bool operator==(const SceneObjectData& object1, const SceneObjectData& object2);

struct RenderSettings
{
public:
    RenderSettings()
        : RenderSettings(1, 2)
    {}

    RenderSettings(unsigned int samplePerPixelParam, unsigned int maxDepthParam)
        : samplePerPixel(samplePerPixelParam)
        , maxDepth(maxDepthParam)
    {}

public:
    unsigned int samplePerPixel;
    unsigned int maxDepth;
};

bool operator==(const RenderSettings& settings1, const RenderSettings& settings2);

class SceneData
{
public:
    SceneData();

    const CameraData& getCameraData() const { return m_camera; }
    const RenderSettings& getRenderSettings() const { return m_renderSettings; }
    const SceneObjectData& getSceneObject(unsigned int index) const { return m_sceneObjects[index]; }
    unsigned int getSceneObjectsCount() const { return m_sceneObjects.size(); }

    std::vector<SceneObjectData>::iterator                  begin() { return m_sceneObjects.begin(); }
    std::vector<SceneObjectData>::iterator                  end() { return m_sceneObjects.end(); }
    std::vector<SceneObjectData>::reverse_iterator          rbegin() { return m_sceneObjects.rbegin(); }
    std::vector<SceneObjectData>::reverse_iterator          rend() { return m_sceneObjects.rend(); }
    std::vector<SceneObjectData>::const_iterator            begin() const { return m_sceneObjects.begin(); }
    std::vector<SceneObjectData>::const_iterator            end() const { return m_sceneObjects.end(); }
    std::vector<SceneObjectData>::const_reverse_iterator    rbegin() const { return m_sceneObjects.rbegin(); }
    std::vector<SceneObjectData>::const_reverse_iterator    rend() const { return m_sceneObjects.rend(); }

    void setCameraData(const CameraData& camera) { m_camera = camera; }

    void addObject(const SceneObjectData& object);
    void addObject(const std::string& name,
                   std::shared_ptr<PrimitiveData> primitive,
                   std::shared_ptr<MaterialData> material);
    void addPlane(const std::string& name,
                  const glm::vec3& position, const glm::vec3& normal,
                  std::shared_ptr<MaterialData> material);
    void addRectangle(const std::string& name,
                      const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2,
                      std::shared_ptr<MaterialData> material);
    void addSphere(const std::string& name,
                   const glm::vec3& position, float radius,
                   std::shared_ptr<MaterialData> material);

    void setRenderSettings(const RenderSettings& renderSettings) { m_renderSettings = renderSettings; }

private:
    CameraData m_camera;
    std::vector<SceneObjectData> m_sceneObjects;
    RenderSettings m_renderSettings;
};

bool operator==(const SceneData& scene1, const SceneData& scene2);

}
