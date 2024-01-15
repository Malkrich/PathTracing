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
        Scene(Camera cam_param);
        void push_back(SceneObject* object);

        /*Getter*/
        Camera const& getCamera() const;
        std::vector<SceneObject*> const& getListObject() const;

        int const size_primitive() const;
        SceneObject* getSceneObject(int index) const;
        Primitive const& get_primitive(int index) const;
        Material const& get_material(int index) const;

    private:
        std::vector<SceneObject*> list_object;
        Camera cam;
    };
}

#endif // SCENE_H
