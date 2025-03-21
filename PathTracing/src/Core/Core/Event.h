#pragma once

#include <functional>

namespace PathTracing
{

    #define WRITE_TYPE_GETTERS(type) \
        inline virtual EventType getType() const override { return type; } \
        inline static EventType getTypeStatic() { return type; }

    enum class EventType
    {
        WindowClose, WindowResize,
        MouseMove,
        KeyPressed, KeyReleased
    };

    class Event
    {
    public:
        inline virtual EventType getType() const = 0;

        inline bool isHandled() const { return m_handle; }

    private:
        bool m_handle = false;

        friend class EventDispatcher;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        WRITE_TYPE_GETTERS(EventType::WindowClose)
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_width(width)
            , m_height(height)
        {}

        WRITE_TYPE_GETTERS(EventType::WindowResize)

        inline unsigned int getWidth() const { return m_width; }
        inline unsigned int getHeight() const { return m_height; }
    private:
        unsigned int m_width, m_height;
    };

    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(unsigned int posX, unsigned int posY)
            : m_posX(posX)
            , m_posY(posY)
        {}

        WRITE_TYPE_GETTERS(EventType::MouseMove)

        inline unsigned int getPosX() const { return m_posX; }
        inline unsigned int getPosY() const { return m_posY; }

    private:
        unsigned int m_posX, m_posY;
    };

    class KeyEvent : public Event
    {
    public:
        KeyEvent(uint32_t keyCode)
            : m_keyCode(keyCode)
        {}

        uint32_t getKeyCode() const { return m_keyCode; }

    private:
        uint32_t m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(uint32_t keyCode)
            : KeyEvent(keyCode)
        {}

        WRITE_TYPE_GETTERS(EventType::KeyPressed);
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(uint32_t keyCode)
            : KeyEvent(keyCode)
        {}

        WRITE_TYPE_GETTERS(EventType::KeyReleased);
    };

    class EventDispatcher
    {
    public:
        typedef std::function<void(Event&)> EventCallbackFn;

    public:
        EventDispatcher(Event& e)
            : m_event(e)
        {}

        template<typename T>
        void dispatch(std::function<bool(T&)> callbackFunction)
        {
            if (!m_event.m_handle && m_event.getType() == T::getTypeStatic())
            {
                m_event.m_handle = callbackFunction(*((T*)&m_event));
            }
        }

    private:
        Event& m_event;
    };

}
