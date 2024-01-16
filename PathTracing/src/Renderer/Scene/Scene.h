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

    std::vector<SceneObject*>::iterator begin() { return m_objectList.begin(); }
    std::vector<SceneObject*>::iterator end() { return m_objectList.end(); }
    std::vector<SceneObject*>::reverse_iterator rbegin() { return m_objectList.rbegin(); }
    std::vector<SceneObject*>::reverse_iterator rend() { return m_objectList.rend(); }
    std::vector<SceneObject*>::const_iterator begin() const { return m_objectList.begin(); }
    std::vector<SceneObject*>::const_iterator end() const { return m_objectList.end(); }
    std::vector<SceneObject*>::const_reverse_iterator rbegin() const { return m_objectList.rbegin(); }
    std::vector<SceneObject*>::const_reverse_iterator rend() const { return m_objectList.rend(); }

private:
    std::vector<SceneObject*> m_objectList;
    Camera m_camera;
};
}

#endif // SCENE_H
