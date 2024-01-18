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
    void setSceneData(std::shared_ptr<SceneData> sceneData);
    std::shared_ptr<Image> getImage() const { return m_image; }

    void startRenderingThread();

    void resizeImage(unsigned int width, unsigned int height);

private:
    void updateSceneFromSceneData();

private:
    // scene
    std::shared_ptr<SceneData> m_sceneData;
    std::shared_ptr<Scene> m_scene;

    // image
    std::shared_ptr<Image> m_image;

    bool m_isRendering = false;
    bool m_sceneHasNewData = true;

    unsigned int m_width, m_height;
};

}
