#include "Renderer.h"

#include <string>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include "Core/Application.h"

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

Renderer::Renderer()
    : m_screenImage(Application::get()->getWindow()->getWidth(),
                    Application::get()->getWindow()->getHeight())
{
    initialize();

    for(unsigned int x = 0; x < m_screenImage.getWidth(); x++)
    {
        for(unsigned int y = 0; y < m_screenImage.getHeight(); y++)
            m_screenImage(x, y) = {
                    (float)x / (float)m_screenImage.getWidth(),
                    (float)y / (float)m_screenImage.getHeight(),
                    0.2};
    }
}

void Renderer::begin(const glm::vec3& clearColor) const
{
    /* Render here */
    glClearColor(clearColor.r,
                 clearColor.g,
                 clearColor.b,
                 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw()
{
    glBindTexture(GL_TEXTURE_2D, m_screenTextureId);        CHECK_GL_ERROR();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F,
                 m_screenImage.getWidth(), m_screenImage.getHeight(),
                 0, GL_RGB,  GL_FLOAT,
                 m_screenImage.getData());                  CHECK_GL_ERROR();
    glUseProgram(m_screenProgramId);                        CHECK_GL_ERROR();
    glBindVertexArray(m_screenVao);                         CHECK_GL_ERROR();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    CHECK_GL_ERROR();
}

void Renderer::initialize()
{
    // Screen Quad
    // Shader
    std::string vertexShader    = Utils::read_file("PathTracing/shaders/PathTracerRender.vert");
    std::string fragmentShader  = Utils::read_file("PathTracing/shaders/PathTracerRender.frag");
    m_screenProgramId = Utils::create_program(vertexShader, fragmentShader);

    float screenPositions[] = {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                               -1.5f,  1.0f, 0.0f, 0.0f, 1.0f};

    int screenIndices[] = {0, 1, 2,
                           2, 3, 0};

    unsigned int vbo, ebo;
    glGenVertexArrays(1, &m_screenVao);   // vertex array
    glGenBuffers(1, &vbo);        // vertex buffer
    glGenBuffers(1, &ebo);        // index buffer

    glBindVertexArray(m_screenVao);                                                             CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                         CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenPositions), screenPositions, GL_STATIC_DRAW);    CHECK_GL_ERROR();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);                        CHECK_GL_ERROR();
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))); CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);                                                               CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);                                                               CHECK_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);                                                 CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(screenIndices), screenIndices, GL_STATIC_DRAW);CHECK_GL_ERROR();

    glGenTextures(1, &m_screenTextureId);
    glBindTexture(GL_TEXTURE_2D, m_screenTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

}
