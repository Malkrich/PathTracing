#pragma once

#include <string>

namespace PathTracing
{

class Shader
{
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    void bind() const;

private:
    unsigned int m_programId;
};

}
