#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace PathTracing
{

Window::Window(const WindowSpec& windowSpec)
    : m_windowData(windowSpec)
{
    initialize();
}

void Window::onUpdate()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::initialize()
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    m_window = glfwCreateWindow(m_windowData.Width, m_windowData.Height,
                                m_windowData.name.c_str(),
                                NULL, NULL);
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
