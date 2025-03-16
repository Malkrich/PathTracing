#include "Pch.h"

#include "Application.h"

int main()
{
    PathTracing::Application* app = new PathTracing::Application("Path Tracing");

    app->run();

    delete app;
}
