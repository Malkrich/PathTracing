#pragma once

#include "Event.h"
#include "Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/ImGuiRenderer.h"
#include "Scene/Scene.h"

#include "Panels/ViewportPanel.h"
#include "Panels/RendererSettingsPanel.h"

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

        float m_frameTime = 0.0f;

        // Path tracing renderer
        Renderer m_renderer;
        Scene m_scene;
        Camera m_camera;

        // Panels
        std::unique_ptr<ViewportPanel> m_viewportPanel = nullptr;
        std::unique_ptr<RendererSettingsPanel> m_rendererSettingsPanel = nullptr;

        // Application
        std::shared_ptr<Window> m_window = nullptr;
        std::unique_ptr<ImGuiRenderer> m_imGuiRenderer = nullptr;

        // singleton instance
        static Application* s_instance;
    };

}
