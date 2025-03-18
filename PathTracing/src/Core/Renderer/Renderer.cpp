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

		for (uint32_t bounce = 0; bounce < m_renderSettings.BounceCount; bounce++)
		{
			HitPayload payload = traceRay(ray);

			if (payload.HitDistance < 0.0f)
			{
				glm::vec3 backgroundColor = { 0.1f, 0.1f, 0.1f };
				finalColor += backgroundColor;
				break;
			}

			ray.Position = payload.HitPosition + 0.000001f * payload.HitNormal;
			ray.Direction = glm::reflect(ray.Direction, payload.HitNormal);

			const Material* material = nullptr;
			if (payload.Object == ObjectType::Sphere)
				material = &(m_activeScene->getSphereMaterials()[payload.ObjectIndex]);
			if (payload.Object == ObjectType::Sphere)
				material = &(m_activeScene->getPlaneMaterials()[payload.ObjectIndex]);

			if (material)
				finalColor = material->Albedo;
		}

		return glm::vec4(finalColor, 1.0f);
	}

	Renderer::HitPayload Renderer::traceRay(const Ray& ray)
	{
		int closestObjectIndex = -1;
		ObjectType closestObject = ObjectType::None;
		float closestHitDistance = std::numeric_limits<float>::max();

		// Spheres pass
		{
			const auto& spheres = m_activeScene->getSpheres();
			for (size_t objectIndex = 0; objectIndex < spheres.size(); objectIndex++)
			{
				const Sphere& sphere = spheres[objectIndex];

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
					closestObject = ObjectType::Sphere;
					closestHitDistance = closestT;
					closestObjectIndex = (int)objectIndex;
				}
			}
		}

		// Plane pass
		{
			const auto& planes = m_activeScene->getPlanes();
			for (size_t objectIndex = 0; objectIndex < planes.size(); objectIndex++)
			{
				const Plane& plane = planes[objectIndex];

				float t = -1.0f * glm::dot(ray.Position - plane.Position, plane.Normal) / glm::dot(ray.Direction, plane.Normal);

				if (t < 0.0f)
					continue;

				if (t < closestHitDistance)
				{
					closestObject = ObjectType::Plane;
					closestHitDistance = t;
					closestObjectIndex = (int)objectIndex;
				}
			}
		}

		if (closestObjectIndex < 0)
			return miss(ray);

		return hit(ray, closestObject, closestObjectIndex, closestHitDistance);
	}

	Renderer::HitPayload Renderer::miss(const Ray& ray)
	{
		HitPayload payload;
		return payload;
	}

	Renderer::HitPayload Renderer::hit(const Ray& ray, ObjectType object, int objectIndex, const float hitDistance)
	{
		HitPayload payload;

		payload.HitDistance = hitDistance;
		payload.HitPosition = ray.Position + ray.Direction * hitDistance;
		payload.Object = object;
		payload.ObjectIndex = (int)objectIndex;

		switch (object)
		{
			case ObjectType::Sphere:
			{
				const Sphere& closestSphere = m_activeScene->getSpheres()[objectIndex];
				glm::vec3 origin = ray.Position - closestSphere.Position;
				glm::vec3 intersectionPosition = origin + ray.Direction * payload.HitDistance;
				payload.HitNormal = glm::normalize(intersectionPosition);
				break;
			}
			case ObjectType::Plane:
			{
				const Plane& closestPlane = m_activeScene->getPlanes()[objectIndex];
				payload.HitNormal = closestPlane.Normal;
				break;
			}
		}

		return payload;
	}

}