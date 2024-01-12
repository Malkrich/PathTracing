#pragma once

#ifdef PT_GRAPHIC_DEBUG
	#define CHECK_GL_ERROR() ::PathTracing::_check_gl_error(__FILE__,__LINE__)
#else
	#define CHECK_GL_ERROR()
#endif

namespace PathTracing
{

//https://blog.nobel-joergensen.com/2013/01/29/debugging-opengl-using-glgeterror/
void _check_gl_error(const char *file, int line);

}
