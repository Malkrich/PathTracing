#include "Application.h"

#include <iostream>

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
{
}

void Application::run()
{
    const glm::vec3 clearColor = {0.2f, 0.2f, 0.2f};
    while(m_running)
    {
        // GUI RENDER
        m_renderer->begin(clearColor);
//        m_renderer->pathTrace();
        m_renderer->draw();

        m_imGuiRenderer->OnNewFrame();

        ImGui::Begin("Test window");
        ImGui::Text("coucou");
        glm::vec3 color;
        ImGui::ColorPicker3("color", glm::value_ptr(color));
        ImGui::End();

        m_imGuiRenderer->onRender();

        m_window->onUpdate();
    }
}

void Application::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::onWindowResize));
}

bool Application::onWindowClose(const WindowCloseEvent& e)
{
    m_running = false;
    return true;
}

bool Application::onWindowResize(const WindowResizeEvent& e)
{
    std::cout << e.getWidth() << ", " << e.getHeight() << std::endl;
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

    // Renderer
    m_renderer.reset(new Renderer());

    // GUI
    m_imGuiRenderer.reset(new ImGuiRenderer());
}

}
