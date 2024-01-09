#include "Shader.h"

#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include "GraphicCore.h"

namespace Utils
{

/************************************************/
/********* From GPU Introduction class **********/
/************************************************/
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
static int compile_shader(const char* shader_source, int shader_type)
{
    int success;
    char log[128];

    int shader_id;
    shader_id = glCreateShader(shader_type);

    glShaderSource(shader_id, 1, &shader_source, NULL);

    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 128, nullptr, log);
        std::cout << "ERROR: SHADER COMPILATION FAILED\n" << log << std::endl;
    }

    return shader_id;
}

static int create_program(const std::string& vertex_shader, const std::string& fragment_shader)
{
    int success;
    char log[128];

    int vertexShaderId    = compile_shader(vertex_shader.c_str(), GL_VERTEX_SHADER);
    int fragmentShaderId  = compile_shader(fragment_shader.c_str(), GL_FRAGMENT_SHADER);

    int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 128, NULL, log);
        std::cout << "ERROR: SHADER LINKING FAILED\n" << log << std::endl;
    }
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return shaderProgram;
}

}

namespace PathTracing
{

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::string vertexShader    = Utils::read_file(vertexShaderPath);
    std::string fragmentShader  = Utils::read_file(fragmentShaderPath);
    m_programId = Utils::create_program(vertexShader, fragmentShader);
}

void Shader::bind() const
{
    glUseProgram(m_programId); CHECK_GL_ERROR();
}

}
