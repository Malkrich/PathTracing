#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "Core/SceneData.h"
#include "Renderer/Camera.h"
#include "SceneObject.h"

namespace PathTracing
{

class Scene
{
public:
    Scene(const Camera& camera);

    /*Getter*/
    const Camera& getCamera() const { return m_camera; }
    Camera& getCamera() { return m_camera; }
    const std::vector<std::shared_ptr<SceneObject>>& getListObject() const { return m_objectList; }
    const std::vector<int>& getListIndexLight() const { return m_listIndexLight; }
    const std::vector<std::shared_ptr<SceneObject>> getLights() const;
    unsigned int getPrimitiveCount() const { return m_objectList.size(); }
    std::shared_ptr<SceneObject> getSceneObject(int index) const { return m_objectList[index]; }
    std::shared_ptr<Primitive> getPrimitive(int index) const { return getSceneObject(index)->primitive; }
    std::shared_ptr<Material> getMaterial(int index) const { return getSceneObject(index)->material; }
    const RenderSettings& getRenderSettings() const { return m_renderSettings; }

    void addObject(std::shared_ptr<SceneObject> object);
    void setCamera(const Camera& camera) { m_camera = camera; }
    void setRenderSettings(const RenderSettings& renderSettings) { m_renderSettings = renderSettings; }

private:
    std::vector<std::shared_ptr<SceneObject>> m_objectList;
    std::vector<int> m_listIndexLight;
    Camera m_camera;
    RenderSettings m_renderSettings;
};

}

#endif // SCENE_H
