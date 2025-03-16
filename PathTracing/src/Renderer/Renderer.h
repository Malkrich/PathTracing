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

		void onResize(uint32_t width, uint32_t height);

		void renderScene(const Camera& camera, const Scene& scene);

		std::shared_ptr<Image> getImage() const { return m_viewportImage; }

	private:
		const Scene* m_activeScene;
		const Camera* m_activeCamera;

		std::shared_ptr<Image> m_viewportImage;
	};

}