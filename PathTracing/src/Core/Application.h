#pragma once

#include <string>
#include <memory>

#include "Event.h"
#include "Window.h"
#include "Renderer/Renderer.h"
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

    bool onWindowClose(const WindowCloseEvent& e);
    bool onWindowResize(const WindowResizeEvent& e);

private:
    bool m_running = true;

    float m_time = 0.0f;

    std::shared_ptr<Window> m_window;
    std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;

    // singleton instance
    static Application* s_instance;
};

}
