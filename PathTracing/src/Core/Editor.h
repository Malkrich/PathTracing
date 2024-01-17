#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Event.h"
#include "Renderer/Image.h"
#include "Renderer/Scene/Scene.h"

namespace PathTracing
{
void createCornellBoxScene(std::shared_ptr<Scene> scene);

class Editor
{
public:
    Editor();
    ~Editor();

    void onUpdate(float dt);
    void onEvent(Event& e);

    void onGuiRender();

private:
    bool onWindowResizeEvent(const WindowResizeEvent& e);

    void makeGuiForSceneObject(const std::shared_ptr<SceneObject>& sceneObject);

private:
    struct GuiLayoutSettings
    {
        const float m_editorSpace = 150.0f;
    };

private:
    float m_deltaTime = 0.0f;
    const glm::vec3 m_clearColor = { 0.2f, 0.2f, 0.2f };

    std::shared_ptr<Image> m_image;
    std::shared_ptr<Scene> m_scene;

    GuiLayoutSettings m_guiLayoutSettings;
};

}
