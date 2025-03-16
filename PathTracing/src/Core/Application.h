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

        Renderer m_renderer;
        Viewport m_viewport;
        Scene m_scene;
        Camera m_camera;

        ImGuiRenderer m_imGuiRenderer;

        std::shared_ptr<Window> m_window;

        // singleton instance
        static Application* s_instance;
    };

}
