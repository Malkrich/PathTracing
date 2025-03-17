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
		Ray ray;
		// Init ray
		ray.Position = m_activeCamera->getPosition();
		ray.Direction = m_activeCamera->getRayDirections()[x + y * m_width];

		glm::vec3 finalColor{ 0.0f };

		uint32_t totalBounces = 2;
		for (uint32_t bounce = 0; bounce < totalBounces; bounce++)
		{
			HitPayload payload = traceRay(ray);

			if (payload.HitDistance < 0.0f)
			{
				glm::vec3 backgroundColor = { 0.1f, 0.1f, 0.1f };
				finalColor += backgroundColor;
				break;
			}

			ray.Position = payload.HitPosition;
			ray.Direction = glm::reflect(ray.Direction, payload.HitNormal);

			const auto& objectMaterial = m_activeScene->getSphereMaterials()[payload.ObjectIndex];
			finalColor += objectMaterial.Albedo;
		}

		return glm::vec4(finalColor, 1.0f);
	}

	Renderer::HitPayload Renderer::traceRay(const Ray& ray)
	{
		HitPayload payload;

		int closestObjectIndex = -1;
		float closestHitDistance = std::numeric_limits<float>::max();
		for (size_t objectIndex = 0; objectIndex < m_activeScene->getSpheres().size(); objectIndex++)
		{
			const Sphere& sphere = m_activeScene->getSpheres()[objectIndex];

			glm::vec3 sphereCenter = sphere.Position;
			float sphereRadius = sphere.Radius;

			// Ray origin relative to object position
			glm::vec3 origin = ray.Position - sphereCenter;

			float a = glm::dot(ray.Direction, ray.Direction);
			float b = 2.0f * glm::dot(origin, ray.Direction);
			float c = glm::dot(origin, origin) - sphereRadius * sphereRadius;
			float delta = b * b - 4 * a * c;

			// Miss object
			if (delta < 0.0f)
				continue;

			float closestT = (-b - glm::sqrt(delta)) / 2.0f * a;

			if (closestT > 0.0f && closestT < closestHitDistance)
			{
				closestHitDistance = closestT;
				closestObjectIndex = (int)objectIndex;
			}
		}

		if (closestObjectIndex < 0)
			return payload;

		const Sphere& closestSphere = m_activeScene->getSpheres()[closestObjectIndex];
		glm::vec3 origin = ray.Position - closestSphere.Position;

		payload.HitDistance = closestHitDistance;
		payload.HitPosition = ray.Position + ray.Direction * closestHitDistance;
		glm::vec3 intersectionPosition = origin + ray.Direction * payload.HitDistance;
		payload.HitNormal = glm::normalize(intersectionPosition);
		payload.ObjectIndex = (int)closestObjectIndex;
		return payload;
	}

}