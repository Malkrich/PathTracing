#pragma once

#include <string>

#include "Event.h"
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
        EventDispatcher::EventCallbackFn callbackFn;
    };

public:
    Window(const WindowSpec& windowSpec);
    ~Window();

    unsigned int getWidth() const { return m_windowData.Width; }
    unsigned int getHeight() const { return m_windowData.Height; }

    void setEventCallbackFunction(const EventDispatcher::EventCallbackFn& fn)
    {
        m_windowData.callbackFn = fn;
    }

    GLFWwindow* getWindowPtr() const { return m_window; }

    void onUpdate();

private:
    void initialize();

private:
    GLFWwindow* m_window;

    WindowSpec m_windowData;
};

}
