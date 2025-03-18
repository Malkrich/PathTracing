#pragma once

#include "Scene/Scene.h"

namespace PathTracing
{

	class SceneControlPanel
	{
	public:
		SceneControlPanel(Scene* scene);

		void setScene(Scene* scene);

		void onGuiRender();

	private:
		Scene* m_activeScene;
	};

}