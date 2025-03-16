#pragma once

#include "Event.h"
#include "Renderer/Image.h"

struct GLFWwindow;

namespace PathTracing
{

    struct WindowSpecifications
    {
        uint32_t Width = 1280;
        uint32_t Height = 720;
        std::string Name = "Unknown Window";
        EventDispatcher::EventCallbackFn callbackFn;

        WindowSpecifications() = default;
    };

    class Window
    {
    public:
        Window(const WindowSpecifications& windowSpec);
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
        GLFWwindow* m_window = nullptr;

        WindowSpecifications m_windowData;
    };

}
