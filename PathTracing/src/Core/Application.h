#pragma once

#include <string>
#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/ImGuiRenderer.h"
#include "Window.h"

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

private:
    bool m_running = true;

    std::shared_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;

    // singleton instance
    static Application* s_instance;
};

}
