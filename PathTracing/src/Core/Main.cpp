#include "Application.h"

int main()
{
    PathTracing::Application* app = new PathTracing::Application("Path Tracing");

    app->run();

    delete app;

    return 0;
}
