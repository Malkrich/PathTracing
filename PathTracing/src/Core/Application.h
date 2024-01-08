#include <string>
#include <memory>

#include "Renderer/ImGuiRenderer.h"

struct GLFWwindow;

//https://blog.nobel-joergensen.com/2013/01/29/debugging-opengl-using-glgeterror/
void _check_gl_error(const char *file, int line);
#define CHECK_GL_ERROR() _check_gl_error(__FILE__,__LINE__)

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

    // buffer IDs
    unsigned int m_vao, m_vbo, m_ebo;
    // shader program ID
    unsigned int m_programId;

    // singleton instance
    static Application* s_instance;
};

}
