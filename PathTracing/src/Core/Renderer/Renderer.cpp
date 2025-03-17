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

	struct Ray
	{
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Direction{ 0.0f, 0.0f, 0.0f };
	};

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
		Ray ray;
		//const glm::vec3& xs = ray.getP0();
		//const glm::vec3& u = ray.getU();
		ray.Position = m_activeCamera->getPosition();
		ray.Direction = m_activeCamera->getRayDirections()[x + y * m_width];

		for (const auto& sphere : m_activeScene->Spheres)
		{
			//const glm::vec3& x0 = m_center;
			//const float r = m_radius;
			glm::vec3 position = sphere.Position;
			float radius = sphere.Radius;

			// Local space origin
			glm::vec3 origin = ray.Position - position;

			//float a = pow(glm::length(u), 2);
			//float b = 2 * dot(xs - x0, u);
			//float c = pow(glm::length(xs - x0), 2) - pow(r, 2);
			float a = glm::dot(ray.Direction, ray.Direction);
			float b = 2.0f * glm::dot(origin, ray.Direction);
			float c = glm::dot(origin, origin) - radius * radius;
			float delta = b * b - 4 * a * c;

			// Miss object
			if (delta < 0.0f)
				continue;

			return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			//float t1 = (-b - glm::sqrt(delta)) / 2.0f * a;

		}

		//if (delta > 0.0f)
		//{
		//	float t1 = (-b - sqrt(delta)) / 2 * a;
		//	float t2 = (-b + sqrt(delta)) / 2 * a;

		//	if (t1 >= 0.0f)
		//	{
		//		glm::vec3 x_inter = xs + t1 * u;
		//		glm::vec3 n = glm::normalize(x_inter - x0);
		//		intersection.set(x_inter, n, t1);
		//		return true;
		//	}
		//	else if (t2 >= 0.0f)
		//	{
		//		glm::vec3 x_inter = xs + t2 * u;
		//		glm::vec3 n = glm::normalize(x_inter - x0);
		//		intersection.set(x_inter, n, t2);
		//		return true;
		//	}
		//	else
		//		return false;
		//}
		//else if (delta == 0.0f)
		//{
		//	float t = -b / 2 * a;
		//	if (t >= 0.0f)
		//	{
		//		glm::vec3 x_inter = xs + t * u;
		//		glm::vec3 n = glm::normalize(x_inter - x0);
		//		intersection.set(x_inter, n, t);
		//		return true;
		//	}
		//	else
		//		return false;
		//}
		//else
		//	return false;

		glm::vec3 backgroundColor = { 0.1f, 0.1f, 0.1f };
		return glm::vec4(backgroundColor, 1.0f);
	}

}