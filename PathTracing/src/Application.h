#include <string>

namespace PathTracing
{

class Application
{
public:
    Application(const std::string& appName);

    void run();

private:
    void initialize();

private:
    bool m_running = true;

    // singleton instance
    static Application* s_instance;
};

}
