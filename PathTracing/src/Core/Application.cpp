#include "Application.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Image.h"

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
    const glm::vec3 clearColor = {0.2f, 0.2f, 0.2f};
    while(!glfwWindowShouldClose(m_window->getWindowPtr()))
    {
        // GUI RENDER
        m_renderer->begin(clearColor);
//        m_renderer->submit(scene);
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

    glfwTerminate();
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
