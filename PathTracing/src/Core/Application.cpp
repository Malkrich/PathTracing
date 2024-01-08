#include "Application.h"

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

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
    glClearColor(0.3, 0.3, 0.3, 1.0);

    while(!glfwWindowShouldClose(m_window))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);

       m_imGuiRenderer->OnNewFrame();

       ImGui::Begin("Test window");
       ImGui::Text("coucou");
       float color[3];
       ImGui::ColorPicker3("color", color);
       ImGui::End();

       m_imGuiRenderer->onRender();

       /* Swap front and back buffers */
       glfwSwapBuffers(m_window);

       /* Poll for and process events */
       glfwPollEvents();
    }

    glfwTerminate();
}

void Application::initialize(const std::string& appName)
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    m_window = glfwCreateWindow(1280, 720, appName.c_str(), NULL, NULL);
    if(!m_window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    m_imGuiRenderer.reset(new ImGuiRenderer());
}

}
