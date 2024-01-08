#include <string>
#include <memory>

#include "Renderer/ImGuiRenderer.h"

struct GLFWwindow;

namespace PathTracing
{

class Application
{
public:
    Application(const std::string& appName);
    ~Application();

    static Application* get() { return s_instance; }

    GLFWwindow* getWindow() { return m_window; }

    void run();

private:
    void initialize(const std::string& appName);

private:
    bool m_running = true;

    GLFWwindow* m_window;

    std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;

    // singleton instance
    static Application* s_instance;
};

}
