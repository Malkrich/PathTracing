#pragma once

#include "Scene/Scene.h"

namespace PathTracing
{

	class SceneControlPanel
	{
	public:
		SceneControlPanel(Scene* scene);

		void setScene(Scene* scene);

		bool onGuiRender();

	private:
		void drawSphereGui(Sphere& sphere);
		void drawPlaneGui(Plane& plane);

	private:
		Scene* m_activeScene = nullptr;

		bool m_guiModified = false;
	};

}