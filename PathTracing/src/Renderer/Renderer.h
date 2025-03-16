#pragma once

#include "Image.h"
#include "Camera.h"
#include "Scene/Scene.h"

namespace PathTracing
{

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void onResize(uint32_t width, uint32_t height);

		void renderScene(const Camera& camera, const Scene& scene);

		const uint32_t* getFinalImageData() const { return m_finalImageData; }

	private:
		glm::vec4 perPixel(uint32_t x, uint32_t y);

	private:
		const Scene* m_activeScene;
		const Camera* m_activeCamera;

		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t* m_finalImageData = nullptr;
	};

}