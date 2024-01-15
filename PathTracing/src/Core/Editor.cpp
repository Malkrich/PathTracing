#include "Editor.h"

#include <iostream>
#include <string>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Base.h"
#include "Application.h"
#include "Renderer/Renderer.h"

namespace PathTracing
{
	Editor::Editor()
	{
		// has to be called first
		Renderer::init();

        m_image.reset(new Image32UI(Renderer::getViewportWidth(), Renderer::getViewportHeight()));
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
        Renderer::pathTrace(m_image);
		Renderer::draw(m_image);
	}

	void Editor::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Editor::onWindowResizeEvent));
	}

	bool Editor::onWindowResizeEvent(const WindowResizeEvent& e)
	{
		m_image->resize(e.getWidth(), e.getHeight());
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

        std::string infoDimension = "Dimension : ["
                + std::to_string(Renderer::getViewportWidth()) + ", "
                + std::to_string(Renderer::getViewportHeight()) + "]";

        ImGui::Begin("Info : ");
		ImGui::Text(timeStat.c_str());
		ImGui::Text(fpsStat.c_str());
        ImGui::Text("");
        ImGui::Text(infoDimension.c_str());
		ImGui::End();
	}

}
