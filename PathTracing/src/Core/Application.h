#pragma once

#include "Event.h"
#include "Window.h"
#include "Viewport.h"
#include "Renderer/Renderer.h"
#include "Renderer/ImGuiRenderer.h"
#include "Scene/Scene.h"

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

        // Path tracing renderer
        Renderer m_renderer;
        Scene m_scene;
        Camera m_camera;

        // Application
        std::unique_ptr<Viewport> m_viewport;
        std::shared_ptr<Window> m_window;
        std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;

        // singleton instance
        static Application* s_instance;
    };

}
