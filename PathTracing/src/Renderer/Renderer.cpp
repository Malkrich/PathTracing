#include "Pch.h"

#include "Renderer.h"

namespace PathTracing
{

	Renderer::Renderer()
	{
	}

	void Renderer::onResize(uint32_t width, uint32_t height)
	{
		m_viewportImage->resize(width, height);
	}

	void Renderer::renderScene(const Camera& camera, const Scene& scene)
	{
		m_activeCamera = &camera;
		m_activeScene = &scene;

		for (uint32_t y = 0; y < m_viewportImage->getHeight(); y++)
		{
			for (uint32_t x = 0; x < m_viewportImage->getWidth(); x++)
			{
				m_viewportImage->setData(x, y, { 1.0f, 0.0f, 1.0f, 1.0f });
			}
		}
	}

}