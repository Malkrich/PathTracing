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
    void makeGuiForResetButton(const std::string& name, void(*resetFunction)(SceneData&));
    void makeGuiForSceneObject(const SceneObjectData& sceneObject);

private:
    struct GuiLayoutSettings
    {
        const float parameterOffset     = 150.0f;
        const float resetButtonOffset   = 90.0f;
    };

private:
    float m_deltaTime = 0.0f;

    std::shared_ptr<SceneData> m_sceneData;

    GuiLayoutSettings m_guiLayoutSettings;
};

}
