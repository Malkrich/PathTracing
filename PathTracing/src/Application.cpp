#include "Application.h"

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);

    while(!glfwWindowShouldClose(m_window))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);

       // NEW FRAME
       ImGui_ImplOpenGL3_NewFrame();
       ImGui_ImplGlfw_NewFrame();
       ImGui::NewFrame();

       ImGuiIO& io = ImGui::GetIO();
       int width, height;
       glfwGetWindowSize(m_window, &width, &height);
       io.DisplaySize = ImVec2((float)width, (float)height);

       float time = (float)glfwGetTime();
       io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
       m_time = time;

       ImGui::Begin("Test window");
       ImGui::Text("coucou");
       float color[3];
       ImGui::ColorPicker3("color", color);
       ImGui::End();

       // IMGUI RENDER
       ImGui::Render();
       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
       if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
       {
           ImGui::UpdatePlatformWindows();
           ImGui::RenderPlatformWindowsDefault();
           glfwMakeContextCurrent(m_window);
       }

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

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // GLFW
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

}
