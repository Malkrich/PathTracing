#include "Application.h"

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace PathTracing
{

Application* Application::s_instance = nullptr;

Application::Application(const std::string& appName)
{
    s_instance = this;

    initialize(appName);
}

void Application::run()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);

    unsigned int vbo;
    glGenBuffers(1, &vbo);

    while(!glfwWindowShouldClose(m_window))
    {
        /* Render here */
       glClear(GL_COLOR_BUFFER_BIT);

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
}

}
