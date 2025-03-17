#include "Pch.h"

#include "Time.h"

#include <GLFW/glfw3.h>

namespace PathTracing
{

	float Time::getTime()
	{
		return glfwGetTime();
	}

}