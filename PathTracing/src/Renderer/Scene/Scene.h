#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "Renderer/Camera.h"
#include "SceneObject.h"

namespace PathTracing
{

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

class Scene
{
public:
    Scene(const Camera& camera);

    /*Getter*/
    const Camera& getCamera() const { return m_camera; }
    Camera& getCamera() { return m_camera; }
    const std::vector<std::shared_ptr<SceneObject>>& getListObject() const { return m_objectList; }
    unsigned int getPrimitiveCount() const { return m_objectList.size(); }
    std::shared_ptr<SceneObject> getSceneObject(int index) const { return m_objectList[index]; }
    std::shared_ptr<Primitive> getPrimitive(int index) const { return getSceneObject(index)->primitive; };
    std::shared_ptr<Material> getMaterial(int index) const { return getSceneObject(index)->material; }
    const RenderSettings& getRenderSettings() const { return m_renderSettings; }

    void addObject(std::shared_ptr<SceneObject> object);
    void setCamera(const Camera& camera) { m_camera = camera; }
    void setRenderSettingds(const RenderSettings& renderSettings) { m_renderSettings = renderSettings; }

    std::vector<std::shared_ptr<SceneObject>>::iterator begin() { return m_objectList.begin(); }
    std::vector<std::shared_ptr<SceneObject>>::iterator end() { return m_objectList.end(); }
    std::vector<std::shared_ptr<SceneObject>>::reverse_iterator rbegin() { return m_objectList.rbegin(); }
    std::vector<std::shared_ptr<SceneObject>>::reverse_iterator rend() { return m_objectList.rend(); }
    std::vector<std::shared_ptr<SceneObject>>::const_iterator begin() const { return m_objectList.begin(); }
    std::vector<std::shared_ptr<SceneObject>>::const_iterator end() const { return m_objectList.end(); }
    std::vector<std::shared_ptr<SceneObject>>::const_reverse_iterator rbegin() const { return m_objectList.rbegin(); }
    std::vector<std::shared_ptr<SceneObject>>::const_reverse_iterator rend() const { return m_objectList.rend(); }

private:
    std::vector<std::shared_ptr<SceneObject>> m_objectList;
    Camera m_camera;
    RenderSettings m_renderSettings;
};

}

#endif // SCENE_H
