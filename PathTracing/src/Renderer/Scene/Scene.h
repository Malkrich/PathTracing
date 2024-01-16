#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Renderer/Camera.h"
#include "SceneObject.h"

namespace PathTracing
{
class Scene
{
public:
    Scene();
    Scene(const Camera& camera);

    /*Getter*/
    const Camera& getCamera() const { return m_camera; }
    Camera& getCamera() { return m_camera; }
    const std::vector<SceneObject*>& getListObject() const { return m_objectList; }
    unsigned int getPrimitiveCount() const { return m_objectList.size(); }
    const SceneObject* getSceneObject(int index) const { return m_objectList[index]; }
    const Primitive* getPrimitive(int index) const { return getSceneObject(index)->primitive; };
    const Material* getMaterial(int index) const { return getSceneObject(index)->material; }

    void addObject(SceneObject* object);
    void setCamera(const Camera& camera) { m_camera = camera; }

private:
    std::vector<SceneObject*> m_objectList;
    Camera m_camera;
};
}

#endif // SCENE_H
