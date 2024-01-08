#include "Application.h"

#include <iostream>
#include <functional>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

void _check_gl_error(const char *file, int line) {
    GLenum err (glGetError());

    while(err!=GL_NO_ERROR) {
        std::string error;
        switch(err) {
        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        case GL_STACK_UNDERFLOW:        error="GL_STACK_UNDERFLOW";     break;
        case GL_STACK_OVERFLOW:         error="GL_STACK_OVERFLOW";      break;
        }
        std::cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<< std::endl;
        err=glGetError();
    }
}

namespace Utils
{

// Renvoi le contenu d'un fichier
static std::string read_file(const std::string& filename)
{
    std::ifstream ifs;
    ifs.open(filename.c_str());
    if (!ifs)
    {
        std::cout << "ERROR: FILE " << filename << " NOT FOUND" << std::endl;
    }
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

// Creation d'un shader
// shader_source : code GLSL
// shader_type : enum représentant le type de shader (GL_VERTEX_SHADER ou GL_FRAGMENT_SHADER)
// Renvoie l'identifiant du shader
static int compile_shader(const char* shader_source, int shader_type)
{
    int success;
    char log[128];

    // TODO:
    // Créer un shader vide -> glCreateShader(GLenum)

    int shader_id;
    shader_id = glCreateShader(shader_type);

    // Mettre le code voulu dans le shader
    //  -> glShaderSource(GLuint, 1, const GLchar * const *, NULL);

    glShaderSource(shader_id, 1, &shader_source, NULL);

    // Compiler le shader -> glCompileShader(GLuint);

    glCompileShader(shader_id);

    // FIN TODO

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 128, nullptr, log);
        std::cout << "ERROR: SHADER COMPILATION FAILED\n" << log << std::endl;
    }

    return shader_id;
}

// Creation programme GPU (vertex + fragment)
// vertex_shader : Contenu du shader
// fragment_shader : Contenu du shader
// Renvoie l'identifiant du programme
static int create_program(const std::string& vertex_shader, const std::string& fragment_shader)
{
    int success;
    char log[128];

    // TODO:
    // (1) : Récupérer le vertex et le fragment shader compilé (utilisez std::string::c_str)

    int vertexShaderId    = compile_shader(vertex_shader.c_str(), GL_VERTEX_SHADER);
    int fragmentShaderId  = compile_shader(fragment_shader.c_str(), GL_FRAGMENT_SHADER);

    // (2) : Créer un nouveau programmme vide GPU -> glCreateProgram()

    int shaderProgram;
    shaderProgram = glCreateProgram();

    // (3) : Lier les deux shader au programme GPU -> glAttachShader(GLuint, GLuint)

    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);

    // (4) : Lier le programme a la CG -> glGetLinkProgram()

    glLinkProgram(shaderProgram);

    // FIN TODO

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 128, NULL, log);
        std::cout << "ERROR: SHADER LINKING FAILED\n" << log << std::endl;
    }

    // TODO
    // Supprimer les deux shaders -> glDeleteShader(GLuint)

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    // FIN TODO

    return shaderProgram;
}

}

namespace PathTracing
{

Application* Application::s_instance = nullptr;

Application::Application(const std::string& appName)
{
    s_instance = this;

    initialize(appName);
}

Application::~Application()
{
}

void Application::run()
{
    while(!glfwWindowShouldClose(m_window))
    {
        /* Render here */
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_programId);                              CHECK_GL_ERROR();
        glBindVertexArray(m_vao);                               CHECK_GL_ERROR();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    CHECK_GL_ERROR();

        // GUI RENDER
        m_imGuiRenderer->OnNewFrame();

        ImGui::Begin("Test window");
        ImGui::Text("coucou");
        float color[3];
        ImGui::ColorPicker3("color", color);
        ImGui::End();

        m_imGuiRenderer->onRender();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::initialize(const std::string& appName)
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    m_window = glfwCreateWindow(1280, 720, appName.c_str(), NULL, NULL);
    if(!m_window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    m_imGuiRenderer.reset(new ImGuiRenderer());

    std::string vertexShader    = Utils::read_file("PathTracing/shaders/PathTracerRender.vert");
    std::string fragmentShader  = Utils::read_file("PathTracing/shaders/PathTracerRender.frag");
    m_programId = Utils::create_program(vertexShader, fragmentShader);

    float positions[] = {-1.0f, -1.0f, 0.0f,
                          1.0f, -1.0f, 0.0f,
                          1.0f,  1.0f, 0.0f,
                         -1.5f,  1.0f, 0.0f};

    int indices[] = {0, 1, 2,
                     2, 3, 0};

    glGenVertexArrays(1, &m_vao);   // vertex array
    glGenBuffers(1, &m_vbo);        // vertex buffer
    glGenBuffers(1, &m_ebo);        // index buffer

    glBindVertexArray(m_vao);                                                           CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);                                               CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);        CHECK_GL_ERROR();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);          CHECK_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);                                       CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);    CHECK_GL_ERROR();

    glEnableVertexAttribArray(0);                                                       CHECK_GL_ERROR();
}

}
