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
    for(unsigned int x = 0; x < s_renderData->image->getWidth(); x++)
    {
        for(unsigned int y = 0; y < s_renderData->image->getHeight(); y++)
        {
            (*s_renderData->image)(x, y) = {0.2f, 0.2f, 0.2f};
        }
    }
}

void Renderer::draw()
{
    s_renderData->screen->draw(s_renderData->image);
}

void Renderer::resize(unsigned int width, unsigned int height)
{
    s_renderData->screen->resize(width, height);
    s_renderData->image->resize(width, height);
}

}
