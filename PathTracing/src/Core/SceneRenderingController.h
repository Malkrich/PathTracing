#pragma once

#include <memory>

#include "SceneData.h"
#include "Renderer/Image.h"
#include "Renderer/Scene/Scene.h"

namespace PathTracing
{

class SceneRenderingController
{
public:
    SceneRenderingController();

    bool isRendering() const { return m_isRendering; }
    void setSceneData(std::shared_ptr<SceneData> sceneData) { m_sceneData = sceneData; updateSceneFromSceneData(); }
    std::shared_ptr<Image> getImage() const { return m_image; }

    void startRenderingThread();

private:
    void updateSceneFromSceneData();

private:
    // scene
    std::shared_ptr<SceneData> m_sceneData;
    std::shared_ptr<Scene> m_scene;

    // image
    std::shared_ptr<Image> m_image;

    bool m_isRendering = false;
};

}
