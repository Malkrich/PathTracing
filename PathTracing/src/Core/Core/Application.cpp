#include "Pch.h"
#include "Application.h"

#include "Base.h"
#include "Time.h"

namespace PathTracing
{

    Application* Application::s_instance = nullptr;

    Application::Application(const std::string& appName)
    {
        s_instance = this;

        initialize(appName);
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while(m_running)
        {
            float time = Time::getTime();
            float dt = time - m_frameTime;
            m_frameTime = time;

            for (auto layer : *m_layerStack)
                layer->onUpdate(dt);

            m_imGuiRenderer->OnNewFrame();
            for (auto layer : *m_layerStack)
                layer->onGuiRender();
            m_imGuiRenderer->onRender();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& e)
    {
        for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
        {
            if (e.isHandled())
                break;

            (*(--it))->onEvent(e);
        }

        // Internal events
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
    }

    bool Application::onWindowClose(const WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }

    void Application::initialize(const std::string& appName)
    {
        uint32_t initialWidth = 1280;
        uint32_t initialHeight = 720;

        // Window handler
        WindowSpecifications windowSpecs;
        windowSpecs.Name     = appName;
        windowSpecs.Width    = initialWidth;
        windowSpecs.Height   = initialHeight;
        m_window = std::make_shared<Window>(windowSpecs);
        m_window->setEventCallbackFunction(BIND_EVENT_FN(Application::onEvent));

        m_imGuiRenderer = std::make_unique<ImGuiRenderer>();

        m_layerStack = std::make_unique<LayerStack>();
    }

}
