#pragma once

#include "Image.h"
#include "Camera.h"
#include "Scene/Scene.h"

namespace PathTracing
{

	class Renderer
	{
	public:
		struct Ray
		{
			glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
			glm::vec3 Direction{ 0.0f, 0.0f, 0.0f };
		};

		struct HitPayload
		{
			float HitDistance = -1.0f;

			glm::vec3 HitPosition{ 0.0f };
			glm::vec3 HitNormal{ 0.0f };

			int ObjectIndex = -1;
		};

	public:
		Renderer();
		~Renderer();

		void onResize(uint32_t width, uint32_t height);

		void renderScene(const Camera& camera, const Scene& scene);

		const uint32_t* getFinalImageData() const { return m_finalImageData; }

	private:
		glm::vec4 perPixel(uint32_t x, uint32_t y);

		HitPayload traceRay(const Ray& ray);

	private:
		const Scene* m_activeScene;
		const Camera* m_activeCamera;

		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t* m_finalImageData = nullptr;
	};

}