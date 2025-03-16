#include "Pch.h"

#include "RendererSettingsPanel.h"

#include <imgui.h>

namespace PathTracing
{

	void RendererSettingsPanel::onUpdate(float deltaTime)
	{
		m_deltaTime = deltaTime;
	}

	void RendererSettingsPanel::onGuiRender()
	{
		ImGui::Begin("Renderer Settings");
		ImGui::Text("%.3f ms", m_deltaTime * 1000.0f);
		ImGui::End();
	}

}