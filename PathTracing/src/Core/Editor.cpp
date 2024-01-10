#include "Editor.h"

#include <iostream>
#include <string>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Base.h"
#include "Renderer/Renderer.h"

namespace PathTracing
{

	Editor::Editor()
	{
		Renderer::init();
	}

	Editor::~Editor()
	{
		Renderer::shutdown();
	}

	void Editor::onUpdate(float dt)
	{
		m_deltaTime = dt;
		// Renderer render
		Renderer::begin(m_clearColor);
		Renderer::pathTrace();
		Renderer::draw();
	}

	void Editor::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Editor::onWindowResizeEvent));
	}

	bool Editor::onWindowResizeEvent(const WindowResizeEvent& e)
	{
		Renderer::resize(e.getWidth(), e.getHeight());
		return true;
	}

	void Editor::onGuiRender()
	{
		std::string timeStat = "Delta time : ";
		timeStat += std::to_string(m_deltaTime * 1000.0f) + " ms";
		float fps = 1 / m_deltaTime;
		std::string fpsStat = "Fps : ";
		fpsStat += std::to_string(fps);

		ImGui::Begin("Statistic : ");
		ImGui::Text(timeStat.c_str());
		ImGui::Text(fpsStat.c_str());
		ImGui::End();
	}

}