#include "Pch.h"

#include "Application.h"
#include "Base.h"
#include "Time.h"
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
            float time = Time::getTime();
            float deltaTime = time - m_frameTime;
            m_frameTime = time;
            m_rendererSettingsPanel->onUpdate(deltaTime);

            uint32_t viewportWidth = m_viewportPanel->getWidth();
            uint32_t viewportHeight = m_viewportPanel->getHeight();
            m_renderer.onResize(viewportWidth, viewportHeight);

            m_renderer.renderScene(m_camera, m_scene);
            const void* imageData = m_renderer.getFinalImageData();
            m_viewportPanel->setViewportImageData(imageData);

            // Panels render
            m_imGuiRenderer->OnNewFrame();
            m_viewportPanel->onGuiRender();
            m_rendererSettingsPanel->onGuiRender();
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

        m_imGuiRenderer = std::make_unique<ImGuiRenderer>();

        // Panels
        m_viewportPanel = std::make_unique<ViewportPanel>();
        m_rendererSettingsPanel = std::make_unique<RendererSettingsPanel>();
    }

}
