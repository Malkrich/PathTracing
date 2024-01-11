#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "SceneObject.h"


namespace PathTracing
{
    class Scene
    {
    public:
        Scene();
        void push_back(SceneObject object);

    private:
        std::vector<SceneObject> list_object;
    };
}

#endif // SCENE_H
