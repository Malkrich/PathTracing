#include "Pch.h"
#include "PathTracingLayer.h"

#include "Core/Application.h"
#include "Renderer/Image.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace PathTracing
{

	PathTracingLayer::PathTracingLayer()
		: m_camera(1280, 720) 
	{
	}

	PathTracingLayer::~PathTracingLayer()
	{
	}

	void PathTracingLayer::onAttach()
	{
		uint32_t windowWidth = Application::get()->getWindow()->getWidth();
		uint32_t windowHeight = Application::get()->getWindow()->getHeight();

		// Panels
		m_viewportPanel = std::make_unique<ViewportPanel>(windowWidth, windowHeight);
		
		{
			Sphere sphere;
			sphere.Position = { 0.0f, 0.0f, -2.0f };
			sphere.Radius = 2.0f;
			Material material;
			material.Albedo = { 1.0f, 1.0f, 1.0f };
			m_scene.addSphere(sphere, material);
		}		
		{
			Sphere sphere;
			sphere.Position = { -0.1f, 0.0f, 0.0f };
			Material material;
			material.Albedo = { 1.0f, 0.0f, 0.0f };
			m_scene.addSphere(sphere, material);
		}
	}

	void PathTracingLayer::onDetach()
	{

	}

	void PathTracingLayer::onUpdate(float dt)
	{
		m_deltaTime = dt;

		uint32_t viewportWidth = m_viewportPanel->getWidth();
		uint32_t viewportHeight = m_viewportPanel->getHeight();
		m_camera.onResize(viewportWidth, viewportHeight);
		m_camera.onUpdate(dt);

		m_renderer.onResize(viewportWidth, viewportHeight);
		m_renderer.renderScene(m_camera, m_scene);
		const void* imageData = m_renderer.getFinalImageData();
		m_viewportPanel->setViewportImageData(imageData);
	}

	void PathTracingLayer::onGuiRender()
	{
		m_viewportPanel->onGuiRender();

		ImGui::Begin("Renderer Settings");
		ImGui::Text("%.3f ms", m_deltaTime * 1000.0f);
		ImGui::End();
	}

	void PathTracingLayer::onEvent(Event& event)
	{

	}

}