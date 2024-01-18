#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Event.h"
#include "SceneData.h"
#include "Renderer/Image.h"

namespace PathTracing
{
void createCornellBoxScene(std::shared_ptr<SceneData> scene);

class Editor
{
public:
    Editor();

    const std::shared_ptr<SceneData> getSceneData() const { return m_sceneData; }

    void onGuiRender();

private:
    void makeGuiForSceneObject(const SceneObjectData& sceneObject);

private:
    struct GuiLayoutSettings
    {
        const float m_editorSpace = 150.0f;
    };

private:
    float m_deltaTime = 0.0f;

    std::shared_ptr<SceneData> m_sceneData;

    GuiLayoutSettings m_guiLayoutSettings;
};

}
