#include "Pch.h"
#include "SceneControlPanel.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace PathTracing
{

	SceneControlPanel::SceneControlPanel(Scene* scene)
		: m_activeScene(scene)
	{
	}

	void SceneControlPanel::setScene(Scene* scene)
	{
		m_activeScene = scene;
	}

	void SceneControlPanel::onGuiRender()
	{
		if (!m_activeScene)
			return;

		ImGui::Begin("Scene");
		// Spheres
		{
			auto& spheres = m_activeScene->Spheres;
			for (size_t i = 0; i < spheres.size(); i++)
			{
				auto& s = spheres[i];
				ImGui::PushID(i);
				ImGui::DragFloat3("Position", (float*)glm::value_ptr(s.Position), 0.05f);
				ImGui::DragFloat("Radius", &s.Radius, 0.05f);
				ImGui::PopID();
			}
		}
		ImGui::End();
	}

}