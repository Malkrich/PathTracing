#include "Pch.h"

#include "Renderer.h"

#include <glm/glm.hpp>

namespace PathTracing
{

	namespace Utils
	{

		uint32_t float4ColorToUint32Color(const glm::vec4& color)
		{
			uint8_t r = (uint8_t)(color.r * 255.0f);
			uint8_t g = (uint8_t)(color.g * 255.0f);
			uint8_t b = (uint8_t)(color.b * 255.0f);
			uint8_t a = (uint8_t)(color.a * 255.0f);

			uint32_t colorResult = 0x00000000 | (r << 24) | (g << 16) | (b << 8) | a;
			return colorResult;
		}

	}

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		delete[] m_finalImageData;
	}

	void Renderer::onResize(uint32_t width, uint32_t height)
	{
		if (m_width != width || m_height != height)
		{
			m_width = width;
			m_height = height;

			delete[] m_finalImageData;
			m_finalImageData = new uint32_t[m_width * m_height];
		}
	}

	void Renderer::renderScene(const Camera& camera, const Scene& scene)
	{
		m_activeCamera = &camera;
		m_activeScene = &scene;

		if (!m_finalImageData)
			return;

		for (uint32_t y = 0; y < m_height; y++)
		{
			for (uint32_t x = 0; x < m_width; x++)
			{
				glm::vec4 color = perPixel(x, y);

				color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));

				uint32_t pixelData = Utils::float4ColorToUint32Color(color);
				m_finalImageData[y * m_width + x] = pixelData;
			}
		}
	}

	glm::vec4 Renderer::perPixel(uint32_t x, uint32_t y)
	{
		return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}

}