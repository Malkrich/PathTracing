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

Window::~Window()
{
    glfwTerminate();
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

    glfwSetWindowUserPointer(m_window, &m_windowData);

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
    {
        WindowSpec* wSpec = (WindowSpec*)glfwGetWindowUserPointer(window);

        WindowCloseEvent e;
        wSpec->callbackFn(e);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        WindowSpec* wSpec = (WindowSpec*)glfwGetWindowUserPointer(window);

        wSpec->Width = width;
        wSpec->Height = height;

        WindowResizeEvent e(width, height);
        wSpec->callbackFn(e);
    });
}

}
