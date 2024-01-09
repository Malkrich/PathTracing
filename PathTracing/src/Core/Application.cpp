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
{
    Renderer::shutdown();
}

void Application::run()
{
    const glm::vec3 clearColor = {0.2f, 0.2f, 0.2f};
    while(m_running)
    {
        // time computation
        float time = glfwGetTime();
        float deltaTime = time - m_time;
        m_time = time;
        std::string timeStat = "Delta time : ";
        timeStat += std::to_string(deltaTime * 1000.0f);
        timeStat += " ms";
        float fps = 1 / deltaTime;
        std::string fpsStat = "Fps : ";
        fpsStat += std::to_string(fps);

        // Renderer render
        Renderer::begin(clearColor);
        Renderer::pathTrace();
        Renderer::draw();

        // GUI RENDER
        m_imGuiRenderer->OnNewFrame();

        ImGui::Begin("Statistic : ");
        ImGui::Text(timeStat.c_str());
        ImGui::Text(fpsStat.c_str());
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
    Renderer::resize(e.getWidth(), e.getHeight());
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
    Renderer::init();

    // GUI
    m_imGuiRenderer.reset(new ImGuiRenderer());
}

}
