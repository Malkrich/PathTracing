#pragma once

#include <string>

#include "Renderer/Image.h"

struct GLFWwindow;

namespace PathTracing
{

class Window
{
public:
    struct WindowSpec
    {
        unsigned int Width, Height;
        std::string name;
    };

public:
    Window(const WindowSpec& windowSpec);

    unsigned int getWidth() const { return m_windowData.Width; }
    unsigned int getHeight() const { return m_windowData.Height; }

    GLFWwindow* getWindowPtr() const { return m_window; }

    void onUpdate();

private:
    void initialize();

private:
    GLFWwindow* m_window;

    WindowSpec m_windowData;
};

}
