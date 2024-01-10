#pragma once

#include <glm/glm.hpp>

#include "Event.h"

namespace PathTracing
{

	class Editor
	{
	public:
		Editor();
		~Editor();

		void onUpdate(float dt);
		void onEvent(Event& e);

		void onGuiRender();

	private:
		bool onWindowResizeEvent(const WindowResizeEvent& e);

	private:
		float m_deltaTime = 0.0f;
		const glm::vec3 m_clearColor = { 0.2f, 0.2f, 0.2f };
	};

}