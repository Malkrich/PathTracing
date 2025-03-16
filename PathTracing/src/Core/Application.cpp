#include "Pch.h"

#include "Application.h"
#include "Base.h"
#include "Renderer/Image.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PathTracing
{

    Application* Application::s_instance = nullptr;

    Application::Application(const std::string& appName)
        : m_camera(1280, 720)
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
            uint32_t viewportWidth = m_viewport->getWidth();
            uint32_t viewportHeight = m_viewport->getHeight();
            m_renderer.onResize(viewportWidth, viewportHeight);

            m_renderer.renderScene(m_camera, m_scene);
            auto rendererResult = m_renderer.getImage();
            m_viewport->setViewportImage(rendererResult);

            // Panels render
            m_imGuiRenderer->OnNewFrame();
            //m_editor->onGuiRender();
            m_viewport->onViewportRender();
            m_imGuiRenderer->onRender();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& e)
    {
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
        // Window handler
        WindowSpecifications windowSpecs;
        windowSpecs.Name     = appName;
        windowSpecs.Width    = 1280;
        windowSpecs.Height   = 720;
        m_window = std::make_shared<Window>(windowSpecs);
        m_window->setEventCallbackFunction(BIND_EVENT_FN(Application::onEvent));

        m_viewport = std::make_unique<Viewport>();
        m_imGuiRenderer = std::make_unique<ImGuiRenderer>();
    }

}
