#pragma once

#include "Core/Event.h"

namespace PathTracing
{

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}

		virtual void onEvent(Event& e) {}
		virtual void onUpdate(float dt) {}
		virtual void onGuiRender() {}
	};

}