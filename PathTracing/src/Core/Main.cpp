//#define CLI

#ifndef CLI
    #include "Application.h"
#else
    #include "Core/Editor.h"
    #include "Renderer/Renderer.h"
    #include "Renderer/Scene/Scene.h"
    #include "Renderer/Camera.h"
    #include "Renderer/Image.h"
#endif

int main()
{
#ifndef CLI
    PathTracing::Application* app = new PathTracing::Application("Path Tracing");

    app->run();

    delete app;
#else
    unsigned int width = 1280;
    unsigned int height = 720;

    PathTracing::Camera camera(width, height);
    std::shared_ptr<PathTracing::Scene> scene = std::make_shared<PathTracing::Scene>(camera);
    PathTracing::createCornellBoxScene(scene);

    std::shared_ptr<PathTracing::Image> image = std::make_shared<PathTracing::Image>(width, height);

    PathTracing::Renderer::pathTrace(image, scene);
#endif
    return 0;
}
