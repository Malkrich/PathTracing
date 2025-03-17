#pragma once

#include "Event.h"
#include "Window.h"
#include "Renderer/ImGuiRenderer.h"
#include "Layer/LayerStack.h"
#include "Layer/Layer.h"

namespace PathTracing
{

    class Application
    {
    public:
        Application(const std::string& appName);
        ~Application();

        static Application* get() { return s_instance; }

        template<typename T>
        void pushLayer()
        {
            m_layerStack->pushLayer<T>();
        }

        const std::shared_ptr<Window> getWindow() const { return m_window; }

        void run();

    private:
        void initialize(const std::string& appName);

        void onEvent(Event& e);

        bool onWindowClose(const WindowCloseEvent&);

    private:
        bool m_running = true;

        float m_frameTime = 0.0f;

        // Application
        std::shared_ptr<Window> m_window = nullptr;
        std::unique_ptr<ImGuiRenderer> m_imGuiRenderer = nullptr;

        // Layers
        std::unique_ptr<LayerStack> m_layerStack = nullptr;

        // singleton instance
        static Application* s_instance;
    };

    Application* createApplication();

}