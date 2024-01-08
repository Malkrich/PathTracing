#include <string>

struct GLFWwindow;

namespace PathTracing
{

class Application
{
public:
    Application(const std::string& appName);

    ~Application();

    void run();

private:
    void initialize(const std::string& appName);

private:
    bool m_running = true;

    float m_time;

    GLFWwindow* m_window;

    // singleton instance
    static Application* s_instance;
};

}
