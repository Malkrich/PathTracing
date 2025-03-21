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
		ImGui::PushID("Spheres");
		{
			auto& spheres = m_activeScene->Spheres;
			for (size_t i = 0; i < spheres.size(); i++)
			{
				ImGui::PushID(i);
				ImGui::SeparatorText("Sphere");
				Sphere& s = spheres[i];
				Material& mat = m_activeScene->SphereMaterials[i];
				drawSphereGui(s);
				drawMaterial(mat);
				ImGui::PopID();
			}
		}
		ImGui::PopID();

		// Planes
		ImGui::PushID("Planes");
		{
			auto& planes = m_activeScene->Planes;
			for (size_t i = 0; i < planes.size(); i++)
			{
				ImGui::PushID(i);
				ImGui::SeparatorText("Plane");
				Plane& p = planes[i];
				Material& mat = m_activeScene->PlaneMaterials[i];
				drawPlaneGui(p);
				drawMaterial(mat);
				ImGui::PopID();
			}
		}
		ImGui::PopID();

		ImGui::End();

		return m_guiModified;
	}

	void SceneControlPanel::drawSphereGui(Sphere& sphere)
	{
		m_guiModified |= ImGui::DragFloat3("Position", (float*)glm::value_ptr(sphere.Position), 0.05f);
		m_guiModified |= ImGui::DragFloat("Radius", &sphere.Radius, 0.05f, 0.0f, std::numeric_limits<float>::max());
	}

	void SceneControlPanel::drawPlaneGui(Plane& plane)
	{
		m_guiModified |= ImGui::DragFloat("Position", (float*)&plane.Position.y, 0.05f);
	}

	void SceneControlPanel::drawMaterial(Material& material)
	{
		m_guiModified |= ImGui::ColorEdit3("Albedo", (float*)glm::value_ptr(material.Albedo));
		m_guiModified |= ImGui::SliderFloat("Roughness", &material.Roughness, 0.0f, 1.0f);
		m_guiModified |= ImGui::ColorEdit3("Emission Color", (float*)glm::value_ptr(material.EmissionColor));
		m_guiModified |= ImGui::DragFloat("Emission Strength", (float*)&material.EmissionStrength, 0.1f, 0.0f, std::numeric_limits<float>::max());
	}

}