#pragma once

#include "Core/Event.h"
#include "Core/Layer/Layer.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"

#include "Panels/ViewportPanel.h"

namespace PathTracing
{

	class PathTracingLayer : public Layer
	{
	public:
		PathTracingLayer();
		virtual ~PathTracingLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void onUpdate(float dt) override;
		virtual void onGuiRender() override;
		virtual void onEvent(Event& event) override;

	private:
		// Path tracing renderer
		Renderer m_renderer;
		Scene m_scene;
		Camera m_camera;

		// Panels
		std::unique_ptr<ViewportPanel> m_viewportPanel = nullptr;

		// Time
		float m_deltaTime = 0.0f;
	};

}