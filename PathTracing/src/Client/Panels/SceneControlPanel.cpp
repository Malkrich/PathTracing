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

	bool SceneControlPanel::onGuiRender()
	{
		if (!m_activeScene)
			return false;

		m_guiModified = false;

		ImGui::Begin("Scene");
		// Spheres
		{
			auto& spheres = m_activeScene->Spheres;
			for (size_t i = 0; i < spheres.size(); i++)
			{
				ImGui::PushID(i);
				auto& s = spheres[i];
				drawSphereGui(s);
				ImGui::PopID();
			}
		}
		ImGui::End();

		return m_guiModified;
	}

	void SceneControlPanel::drawSphereGui(Sphere& sphere)
	{
		m_guiModified |= ImGui::DragFloat3("Position", (float*)glm::value_ptr(sphere.Position), 0.05f);
		m_guiModified |= ImGui::DragFloat("Radius", &sphere.Radius, 0.05f, 0.0f, std::numeric_limits<float>::max());
	}

}