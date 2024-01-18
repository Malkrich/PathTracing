#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Renderer/Primitives/Primitive.h"
#include "Renderer/Primitives/Rectangle.h"
#include "Renderer/Primitives/Plane.h"
#include "Renderer/Primitives/Sphere.h"

namespace PathTracing
{

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
    PlaneData(const glm::vec3& position, const glm::vec3& normal)
        : PrimitiveData(SceneObjectPrimitive::plane, position)
        , m_normal(normal)
    {}

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
    RectangleData(const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2)
        : PrimitiveData(SceneObjectPrimitive::rectangle, position)
        , m_v1(v1)
        , m_v2(v2)
    {}

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
    SphereData(const glm::vec3& position, float radius)
        : PrimitiveData(SceneObjectPrimitive::sphere, position)
        , m_radius(radius)
    {}

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
    lambertien = 0,
    light
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
                          SceneObjectMaterial::lambertien,
                          glm::vec3(0.0f))
    {}

    SceneObjectData(const std::string& name,
                    std::shared_ptr<PrimitiveData> primitive,
                    SceneObjectMaterial material,
                    const glm::vec3& color)
        : name(name)
        , primitive(primitive)
        , material(material)
        , color(color)
    {}

    SceneObjectData(const SceneObjectData& other);

    // global data
    std::string name;

    // geometry data
    std::shared_ptr<PrimitiveData> primitive;

    // material data
    SceneObjectMaterial material;
    glm::vec3 color;
//    std::shared_ptr<MaterialParameter> materialParameter;
};

bool operator==(const SceneObjectData& object1, const SceneObjectData& object2);

struct RenderSettings
{
public:
    RenderSettings()
        : RenderSettings(1, 1)
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

    void addObject(const SceneObjectData& object);
    void addObject(const std::string& name,
                   std::shared_ptr<PrimitiveData> primitive,
                   SceneObjectMaterial material, const glm::vec3& color);
    void addPlane(const std::string& name,
                  const glm::vec3& position, const glm::vec3& normal,
                  SceneObjectMaterial material, const glm::vec3& color);
    void addRectangle(const std::string& name,
                      const glm::vec3& position, const glm::vec3& v1, const glm::vec3& v2,
                      SceneObjectMaterial material, const glm::vec3& color);
    void addSphere(const std::string& name,
                   const glm::vec3& position, float radius,
                   SceneObjectMaterial material, const glm::vec3& color);

    void setRenderSettings(const RenderSettings& renderSettings) { m_renderSettings = renderSettings; }

private:
    std::vector<SceneObjectData> m_sceneObjects;
    RenderSettings m_renderSettings;
};

bool operator==(const SceneData& scene1, const SceneData& scene2);

}
