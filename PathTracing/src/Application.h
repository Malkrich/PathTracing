#include <string>

struct GLFWwindow;

namespace PathTracing
{

class Application
{
public:
    Application(const std::string& appName);

    void run();

private:
    void initialize(const std::string& appName);

private:
    bool m_running = true;

    GLFWwindow* m_window;

    // singleton instance
    static Application* s_instance;
};

}
