#include "Application.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Base.h"
#include "Renderer/Image.h"

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
{}

void Application::run()
{
    while(m_running)
    {
        // time computation
        float time = glfwGetTime();
        float deltaTime = time - m_time;
        m_time = time;

        m_editor->onUpdate(deltaTime);

        // GUI RENDER
        m_imGuiRenderer->OnNewFrame();
        m_editor->onGuiRender();
        m_imGuiRenderer->onRender();

        m_window->onUpdate();
    }
}

void Application::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

    m_editor->onEvent(e);
}

bool Application::onWindowClose(const WindowCloseEvent& e)
{
    m_running = false;
    return true;
}

void Application::initialize(const std::string& appName)
{
    // Window handler
    Window::WindowSpec windowSpec;
    windowSpec.name     = appName;
    windowSpec.Width    = 400;
    windowSpec.Height   = 400;
    m_window.reset(new Window(windowSpec));

    // Renderer
    m_editor.reset(new Editor());

    // GUI
    m_imGuiRenderer.reset(new ImGuiRenderer());
}

}
