#pragma once

#include "Application.h"

extern PathTracing::Application* createApplication();

int main()
{
    PathTracing::Application* app = createApplication();

    app->run();

    delete app;
}
