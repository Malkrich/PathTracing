#pragma once

#include <glm/glm.hpp>

#include "Image.h"

//https://blog.nobel-joergensen.com/2013/01/29/debugging-opengl-using-glgeterror/
void _check_gl_error(const char *file, int line);
#define CHECK_GL_ERROR() _check_gl_error(__FILE__,__LINE__)

namespace PathTracing
{

class Renderer
{
public:
    Renderer();

    void begin(const glm::vec3& clearColor) const;
    void draw();

private:
    void initialize();

private:
    unsigned int m_screenProgramId;
    unsigned int m_screenVao;
    unsigned int m_screenTextureId;

    Image m_screenImage;
};

}
