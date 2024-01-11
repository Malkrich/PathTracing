#include "Renderer.h"

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"
#include "Screen.h"

namespace PathTracing
{

static Screen* s_screen = nullptr;

void Renderer::init()
{
    s_screen = new Screen(Application::get()->getWindow()->getWidth(),
                          Application::get()->getWindow()->getHeight());
}

unsigned int Renderer::getViewportWidth() { return s_screen->getViewportWidth(); }
unsigned int Renderer::getViewportHeight() { return s_screen->getViewportHeight(); }

void Renderer::shutdown()
{
    delete s_screen;
}

void Renderer::begin(const glm::vec3& clearColor)
{
    s_screen->clear(clearColor);
}

void Renderer::pathTrace(std::shared_ptr<Image> image)
{
    for(unsigned int y = 0; y < image->getHeight(); y++)
    {
        for(unsigned int x = 0; x < image->getWidth(); x++)
        {
            glm::vec3 color = { 0.8f, 0.2f, 0.2f };
            image->setData(x, y, color);
        }
    }
}

void Renderer::draw(const std::shared_ptr<Image>& image)
{
    s_screen->draw(image);
}

void Renderer::resize(unsigned int width, unsigned int height)
{
    s_screen->resize(width, height);
}

}
