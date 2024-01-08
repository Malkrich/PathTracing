#include "Application.h"

namespace PathTracing
{

Application* Application::s_instance = nullptr;

Application::Application(const std::string& appName)
{
    s_instance = this;

    initialize();
}

void Application::run()
{
    while(m_running)
    {

    }
}

void Application::initialize()
{

}

}
