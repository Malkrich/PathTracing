#include "Pch.h"
#include "Input.h"

#include "Application.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace PathTracing
{

	namespace Utils
	{
		static int internalCursorModeToGlfwCursorMode(CursorMode mode)
		{
			switch (mode)
			{
				case CursorMode::Normal: return GLFW_CURSOR_NORMAL;
				case CursorMode::Hidden: return GLFW_CURSOR_HIDDEN;
				case CursorMode::Locked: return GLFW_CURSOR_DISABLED;
			}
		}
	}

	bool Input::isKeyPressed(int32_t keyCode)
	{
		auto libWindow = (GLFWwindow*)Application::get()->getWindow()->getWindowPtr();
		int32_t state = glfwGetKey(libWindow, keyCode);

		return state == GLFW_PRESS;
	}

	bool Input::isMouseButtonPressed(int32_t button)
	{
		auto libWindow = (GLFWwindow*)Application::get()->getWindow()->getWindowPtr();
		int32_t state = glfwGetMouseButton(libWindow, button);

		return state == GLFW_PRESS;
	}

	void Input::setCursorMode(CursorMode mode)
	{
		auto libWindow = (GLFWwindow*)Application::get()->getWindow()->getWindowPtr();
		int glfwMode = Utils::internalCursorModeToGlfwCursorMode(mode);
		glfwSetInputMode(libWindow, GLFW_CURSOR, glfwMode);
	}

	glm::ivec2 Input::getWindowSize()
	{
		glm::ivec2 dimension;

		auto libWindow = (GLFWwindow*)Application::get()->getWindow()->getWindowPtr();
		glfwGetWindowSize(libWindow, &dimension.x, &dimension.y);

		return dimension;
	}

	glm::ivec2 Input::getMousePosition()
	{
		auto libWindow = (GLFWwindow*)Application::get()->getWindow()->getWindowPtr();
		glm::dvec2 position;
		glfwGetCursorPos(libWindow, &position.x, &position.y);

		glm::ivec2 mousePosition = {(int32_t)position.x, (int32_t)position.y};
		return mousePosition;
	}

}