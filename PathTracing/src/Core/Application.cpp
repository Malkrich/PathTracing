#include "Application.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Base.h"
#include "Renderer/Image.h"
#include "Renderer/Renderer.h"

namespace PathTracing
{

Application* Application::s_instance = nullptr;

Application::Application(const std::string& appName)
{
    s_instance = this;

    initialize(appName);

    m_window->setEventCallbackFunction(BIND_EVENT_FN(Application::onEvent));
}

Application::~Application()
{
}

void Application::run()
{
    while(m_running)
    {
        Renderer::clear(m_clearColor);

        if(!m_sceneRenderingController->isRendering())
        {
            auto sceneData = m_editor->getSceneData();
            m_sceneRenderingController->setSceneData(sceneData);
            m_sceneRenderingController->resizeImage(m_viewport->getWidth(), m_viewport->getHeight());
            m_sceneRenderingController->startRenderingThread();
        }
        m_viewport->setViewportImage(m_sceneRenderingController->getImage());

        // GUI RENDER
        m_imGuiRenderer->OnNewFrame();
        m_editor->onGuiRender();
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
    Window::WindowSpec windowSpec;
    windowSpec.name     = appName;
    windowSpec.Width    = 1280;
    windowSpec.Height   = 720;
    m_window.reset(new Window(windowSpec));

    // GUI / Editor
    m_editor.reset(new Editor());
    m_sceneRenderingController.reset(new SceneRenderingController());
    m_imGuiRenderer.reset(new ImGuiRenderer());

    // Viewport
    m_viewport.reset(new Viewport());
}

}
