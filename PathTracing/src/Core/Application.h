#pragma once

#include <string>
#include <memory>

#include "Event.h"
#include "Window.h"
#include "Editor.h"
#include "Viewport.h"
#include "SceneRenderingController.h"
#include "Renderer/ImGuiRenderer.h"

namespace PathTracing
{

class Application
{
public:
    Application(const std::string& appName);
    ~Application();

    static Application* get() { return s_instance; }

    const std::shared_ptr<Window> getWindow() const { return m_window; }

    void run();

private:
    void initialize(const std::string& appName);

    void onEvent(Event& e);

    bool onWindowClose(const WindowCloseEvent&);

private:
    bool m_running = true;

    float m_time = 0.0f;
    const glm::vec3 m_clearColor = { 0.2f, 0.2f, 0.2f };

    std::shared_ptr<Window> m_window;
    std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;
    std::unique_ptr<Editor> m_editor;
    std::unique_ptr<Viewport> m_viewport;
    std::unique_ptr<SceneRenderingController> m_sceneRenderingController;

    // singleton instance
    static Application* s_instance;
};

}
