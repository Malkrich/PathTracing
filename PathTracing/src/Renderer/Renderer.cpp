#include "Renderer.h"

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"
#include "Image.h"
#include "Screen.h"

namespace PathTracing
{

struct RenderData
{
    std::shared_ptr<Image> image;
    std::unique_ptr<Screen> screen;
};

static RenderData* s_renderData = nullptr;

void Renderer::init()
{
    s_renderData = new RenderData();

    s_renderData->image.reset(new Image(Application::get()->getWindow()->getWidth(),
                                        Application::get()->getWindow()->getHeight()));
    s_renderData->screen.reset(new Screen());
}

void Renderer::shutdown()
{
    delete s_renderData;
}

void Renderer::begin(const glm::vec3& clearColor)
{
    s_renderData->screen->clear(clearColor);
}

void Renderer::pathTrace()
{
    std::shared_ptr<Image> image = s_renderData->image;

    for(unsigned int x = 0; x < image->getWidth(); x++)
    {
        for(unsigned int y = 0; y < image->getHeight(); y++)
        {
            float r = (float)rand() / (float)RAND_MAX;
            float g = (float)rand() / (float)RAND_MAX;
            float b = (float)rand() / (float)RAND_MAX;
            (*image)(x, y) = {r, g, b};
        }
    }
}

void Renderer::draw()
{
    s_renderData->screen->draw(s_renderData->image);
}

}
